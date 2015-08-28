//
//  mdb_thermostat.c
//  
//
//  Created by Jeff on 15/04/13.
//
//

#include <stdio.h>   /* Standard input/output definitions */
#include <stdlib.h>  
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */
#include <time.h> /* POSIX terminal control definitions */

#include "mdb_log.h"
#include "mdb_mysql.h"
#include "mdb_decode_rfxcom_messages.h"
#include "mdb_encode_messages.h"
#include "mdb_tools.h"


// ----------------------------------------------------------------------------
//  LAST T° SENSOR VALUE FUNCTION / ok a tester
// ----------------------------------------------------------------------------

float last_tp( int th_id )
{
	MYSQL *conn;
	MYSQL_RES *result;
	MYSQL_ROW row;
	
	char packettype[5];
	unsigned char subtype;
	int row_id;
	char row_datetime[16];
	float last_th_tp;
	
	/*Recherche du type de recepteur du thermostat*/	
	conn = mysql_connection();
	result = mysql_select(conn,"SELECT devices.packettype,  devices.subtype FROM devices , thermostat  WHERE thermostat.sensor_id = devices.dc_id AND th_id = %d LIMIT 1;", th_id);
	
	int num_fields = mysql_num_fields(result);
        
        while ((row = mysql_fetch_row(result))){
			strncpy(packettype, row[0], 5);
			//packettype = stringtohex(row[0]);
			subtype = stringtohex(row[1]);
        };
		
    mysql_free_result(result);
	mysql_close(conn);

	log_DEBUG("Thermostat:last_tp function: Thermostat Sensor type: %02hhX",packettype );
	
	/*Recherche de la derniere T° selon le type de thermostat*/	
	conn = mysql_connection();

	if ((strcmp(packettype,"40") == 0) || (strcmp(packettype,"52") == 0) || (strcmp(packettype,"1W28") == 0)){
		result = mysql_select(conn,"SELECT last_update, home_data1 from devices INNER JOIN thermostat ON devices.dc_id = thermostat.sensor_id WHERE th_id = %d LIMIT 1;", th_id);
	}
	else{
		log_ERROR("Packet type not supported for thermostat");
		mysql_free_result(result);
		mysql_close(conn);
		return 0;
	}
	
		num_fields = mysql_num_fields(result);
        
        while ((row = mysql_fetch_row(result))){
			strcpy (row_datetime, row[0]);
			last_th_tp = atof(row[1]);
        };
		
    mysql_free_result(result);
	mysql_close(conn);
	
	log_DEBUG("Thermostat:last_tp function: Starting working with th_id: %d , last: %.2f C at %s \n",th_id,last_th_tp,row_datetime);
	return last_th_tp;
}

float scenario( sc_id )
{	
	float consigne;	
    int day = whichday();
	
	log_DEBUG("Scenario : day number in the week : %d",day);
		
	/*Recherche de la progtramation courante*/	
	
	MYSQL *conn;
	MYSQL_RES *result;
	MYSQL_ROW row;
	
	conn = mysql_connection();
	result = mysql_select(conn,"SELECT tp_prog FROM scenario WHERE sc_id = %d AND ((sc_day= %d) OR (sc_day=0)) AND (sc_periode_start < CURRENT_TIME) AND ( CURRENT_TIME < sc_periode_stop) LIMIT 1;",sc_id,day);
	
	int num_fields = mysql_num_fields(result);
        
        while ((row = mysql_fetch_row(result))){
			consigne = atof(row[0]);
        };
		
    mysql_free_result(result);
	mysql_close(conn);

	return consigne;
}

// ----------------------------------------------------------------------------
//  Thermostat Calculation 
// ----------------------------------------------------------------------------

void thermostat_calc(th_id)
{
	MYSQL *conn;
	MYSQL_RES *result;
	MYSQL_ROW row;
	
	int recept_id;
	char th_use[4];
	char th_mode[10];
	char tempo[4];
	float tp_set;
	int sc_id;
	float tp_consigne;
	float tp_current;
	
	/*Recherche des parametres du thermostat*/	
	conn = mysql_connection();
	result = mysql_select(conn,"SELECT recept_id,th_use,th_mode,tp_set,sc_id FROM thermostat WHERE th_id = %d LIMIT 1;", th_id);
    
	int num_fields = mysql_num_fields(result);
        
        while (row = mysql_fetch_row(result)){
			recept_id = atoi(row[0]);
			strcpy(th_use, row[1]);
			strcpy(th_mode, row[2]);
			tp_set = atof(row[3]);
			sc_id = atoi(row[4]);
        };
		
    mysql_free_result(result);
	mysql_close(conn);
	log_DEBUG("Thermostat_Calc: Working with th_id=%d ,recept_id = %d , on/off : %s , mode: %s , Manual tp_set= %.2f °C, Scenario=%d",th_id,recept_id,th_use,th_mode,tp_set,sc_id);
	
	/*Recherche du mode*/
	
	if (!strcmp(th_use,"on")){
		if (!strcmp(th_mode,"manual")){
			log_DEBUG("Thermostat_Calc: Thermostat %d is on in manual mode", th_id);
			tp_consigne = tp_set;
			tp_current = last_tp(th_id);
			log_DEBUG("Thermostat_Calc: Consigne= %.2f last= %.2f",tp_consigne,tp_current);
			
			 if (tp_consigne > tp_current){
				log_DEBUG("Thermostat_Calc:Send Message ON");
				encode_thermostat_message(recept_id,tp_consigne,tp_current, "demand");
			}
			else{
				log_DEBUG("Thermostat_Calc:Send Message OFF");
				encode_thermostat_message(recept_id,tp_consigne,tp_current, "no demand");
			}
		}
		else if (!strcmp(th_mode,"auto")){
			log_DEBUG("Thermostat_Calc: Thermostat %d is on in auto mode", th_id);
			tp_consigne = scenario(sc_id);
			tp_current = last_tp(th_id);
			log_DEBUG("Thermostat_Calc: Consigne= %.2f last= %.2f",tp_consigne,tp_current);
			
			 if (tp_consigne > tp_current){
				log_DEBUG("Thermostat_Calc:Send Message ON");
            	encode_thermostat_message(recept_id,tp_consigne,tp_current, "demand");
			}
			else{                                               
				log_DEBUG("Thermostat_Calc:Send Message OFF");
                encode_thermostat_message(recept_id,tp_consigne,tp_current, "no demand");
			}
		}
		else{
			log_ERROR("Thermostat_Calc: Thermostat Mode Error");
		}
	}
	else if (!strcmp(th_use,"off")){
		log_DEBUG("Thermostat %d is off",th_id);
		tp_consigne = 0;
		tp_current = 0;
        encode_thermostat_message(recept_id,tp_consigne,tp_current, "no demand");
	}
	else{
		log_ERROR("Thermostat_Calc: Thermostat Status Error");
	}
}

void thermostat()
{
	log_DEBUG("Thermostat: Starting looking for thermostat");

	MYSQL *conn;
	MYSQL_RES *result;
	MYSQL_ROW row;
	
	int th_id;
	
	/*Recherche des parametres du thermostat*/	
	conn = mysql_connection();
	result = mysql_select(conn,"SELECT th_id FROM thermostat");
	
	int num_fields = mysql_num_fields(result);
        
        while ((row = mysql_fetch_row(result))){
			th_id = atof(row[0]);
			thermostat_calc(th_id);
        };
		
    mysql_free_result(result);
	mysql_close(conn);

	log_DEBUG("Thermostat: Thermostat process terminated");
}
