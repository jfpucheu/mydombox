/*
'  mdb_encode_messages.c
'
'  Created by Jeff on 04/04/13.
'
*/


/*
'------------------------------------------------------------------------------------
' Protocol License Agreement
'
' The RFXtrx protocols are owned by RFXCOM, and are protected under applicable
' copyright laws.
'
' ==================================================================================
' = It is only allowed to use this software or any part of it for RFXCOM products. =
' ==================================================================================
'
' The above Protocol License Agreement and the permission notice shall be included
' in all software using the RFXtrx protocols.
'
' Any use in violation of the foregoing restrictions may subject the user to criminal
' sanctions under applicable laws, as well as to civil liability for the breach of the
' terms and conditions of this license.
'------------------------------------------------------------------------------------- 
*/

#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */

#include "mdb_encode_messages.h"
#include "mdb_decode_rfxcom_messages.h"
#include "mdb_log.h"
#include "mdb_mysql.h"
#include "mdb_tools.h"
#include "mdb_rfxtrx433.h"

#define DB_MYSQL 1


/*-----------------------------------------------------------------
/		Encode message lighting
/		working for : 0x11,0x14,0x1A
-------------------------------------------------------------------*/

int encode_lighting_message(int dc_id, char* state, int dim)
{

	log_DEBUG("[Encode Message] Starting Encoding Lighting Message for dc_id: %d, State: %s dim: %d ", dc_id,state,dim);
	
	MYSQL *conn;
	MYSQL_RES *result;
	MYSQL_ROW row;
	
	unsigned char packettype;
	unsigned char subtype;
	unsigned char id1;
	unsigned char id2;
	unsigned char id3;
	unsigned char id4;
	unsigned char unitcode;

	int row_id;
		
	/*Recherche du type de device*/	
	if ( DB_MYSQL == 1){
		conn = mysql_connection();	
		result = mysql_select(conn,"SELECT packettype,subtype,id1,id2,id3,id4,unitcode,groupcode,housecode FROM devices WHERE dc_id=%d LIMIT 1;", dc_id);

        if (result != NULL)
        {
            int num_fields = mysql_num_fields(result);
        
                while ((row = mysql_fetch_row(result))){
                    packettype = stringtohex(row[0]);
                    subtype = stringtohex(row[1]);
                    id1 = stringtohex(row[2]);
                    id2 = stringtohex(row[3]);
                    id3 = stringtohex(row[4]);
                    id4 = stringtohex(row[5]);
                    unitcode = stringtohex(row[6]);
                };
        }
		mysql_free_result(result);
		mysql_close(conn);
	}
	
	log_DEBUG("[Encode Message] Encoding Message for device: %d, Packettype: %02hhX, subtype: %02hhX, id1: %02hhX, id2: %02hhX , id3: %02hhX, id4:%02hhX, unitcode: %02hhX .",dc_id,packettype,subtype,id1,id2,id3,id4,unitcode);
	
	/* ---------------------------------------
    / 0x11 - Lighting2
    / ---------------------------------------*/
	
	if ( packettype == 0x11)
	{
		
		unsigned char message[12];
		
		message[0]= 0X0B;
		message[1]= packettype;
		message[2]= subtype;
		message[3]= 0X00;
		message[4]= id1;
		message[5]= id2;
		message[6]= id3;
		message[7]= id4;
		message[8]= unitcode;

		if (strcmp(state, "off") == 0)
		{
			message[9]= 0x00;
			message[10]= 0x00;
		}
		else if ( strcmp(state, "on") == 0)
		{
			message[9]= 0x01;
			message[10]= 0x0F;
		}
		else if ( strcmp(state, "set level") == 0)
		{
			message[9]= 0x02;
			message[10]= inttohex(dim);
		}		
		else if ( strcmp(state, "group off") == 0)
		{
			message[9]= 0x03;
			message[10]= 0x00;
		}
		else if ( strcmp(state, "group on") == 0)
		{
			message[9]= 0x04;
			message[10]= 0x0F;
		}
		else if ( strcmp(state, "set group level") == 0)
		{
			message[9]= 0x05;
			message[10]= inttohex(dim);
		}
		else
		{
			message[9]= 0x00;
			message[10]= 0x00;		
		}
		
			if( send_message(message) == 0)
			{
			// MYSQL INSERTION
				if ( DB_MYSQL == 1){	
					if (mysql_insert("INSERT INTO state (dc_id,datetime,device_mode,dim_level) VALUES (%d,NOW(),'%s',%d) ON DUPLICATE KEY UPDATE datetime=NOW(),device_mode='%s',dim_level=%d;",dc_id,state,dim,state,dim) == 0);		
				}
			return 0;
			}
			else
			{
				log_ERROR("[Encode Message] Error Sending Message");
				return 1;
			}
	}

	/* ---------------------------------------
    / 0x14 - Lighting5
    / ---------------------------------------*/
	
	else if ( packettype == 0x14)
	{
		
		unsigned char message[12];
		
		message[0]= 0X0A;
		message[1]= packettype;
		message[2]= subtype;
		message[3]= 0X00;
		message[4]= id1;
		message[5]= id2;
		message[6]= id3;
		message[7]= unitcode;

		if (strcmp(state, "Off") == 0)
		{
			message[8]= 0x00;
		}
		else if ( strcmp(state, "On") == 0)
		{
			message[8]= 0x01;
		}
		else if ( strcmp(state, "Bright") == 0)
		{
			message[8]= 0x02;
		}		
		else if ( strcmp(state, "Dim") == 0)
		{
			message[8]= 0x03;
		}
		else if ( strcmp(state, "Color+") == 0)
		{
			message[8]= 0x04;
		}
		else if ( strcmp(state, "Color-") == 0)
		{
			message[8]= 0x05;
		}
		else
		{
			message[8]= stringtohex(state);
			sprintf( state,"Color : %02hhX", message[8] );
		}
		message[9]= 0x00;
		
			if( send_message(message) == 0)
			{
			// MYSQL INSERTION
				if ( DB_MYSQL == 1){
					
					if (mysql_insert("INSERT INTO state (dc_id,datetime,device_mode,dim_level) VALUES (%d,NOW(),'%s',%d) ON DUPLICATE KEY UPDATE datetime=NOW(),device_mode='%s',dim_level=%d;",dc_id,state,dim,state,dim) == 0);
					
				}
			return 0;
			}
			else
			{
				log_ERROR("[Encode Message] Error Sending Message");
				return 1;
			}
	}
	
	/* ---------------------------------------
    / 0x1A - RFY
    / ---------------------------------------*/
	
	else if ( packettype == 0x1A)
	{
		
		unsigned char message[14];
		
		message[0]= 0X0C;
		message[1]= packettype;
		message[2]= subtype;
		message[3]= 0X00;
		message[4]= id1;
		message[5]= id2;
		message[6]= id3;
		message[7]= unitcode;

		//Only the 4 commands implemented in the application!!
		
		if (strcmp(state, "stop") == 0)
		{
			message[8]= 0x00;
		}
		else if ( strcmp(state, "up") == 0)
		{
			message[8]= 0x01;
		}
		else if ( strcmp(state, "down") == 0)
		{
			message[8]= 0x03;
		}		
		else if ( strcmp(state, "Program") == 0)
		{
			message[8]= 0x07;
		}
		else
		{
			message[8]= stringtohex(state);
			sprintf( state,"Color : %02hhX", message[8] );
		}
		message[9]= 0x00;
		
			if( send_message(message) == 0)
			{
			// MYSQL INSERTION
				if ( DB_MYSQL == 1){
					
					if (mysql_insert("INSERT INTO state (dc_id,datetime,device_mode,dim_level) VALUES (%d,NOW(),'%s',%d) ON DUPLICATE KEY UPDATE datetime=NOW(),device_mode='%s',dim_level=%d;",dc_id,state,dim,state,dim) == 0);
					
				}
			return 0;
			}
			else
			{
				log_ERROR("[Encode Message] Error Sending Message");
				return 1;
			}
	}
	else
	{
		log_ERROR("[Encode Message] Not Suported yet");
		return 1;
	}
}

/*-----------------------------------------------------------------
/		Encode message Thermostat
/		working for : 0x40,
-------------------------------------------------------------------*/

int encode_thermostat_message(int dc_id, float tp_consigne, float tp_current, char* demand)
{

	log_DEBUG("[Encode Message] Starting Encoding Thermostat Message for dc_id: %d, tp_consigne: %.2f , tp_current: %.2f , demand: %s", dc_id,tp_consigne,tp_current,demand);
	
	MYSQL *conn;
	MYSQL_RES *result;
	MYSQL_ROW row;
	
	unsigned char packettype;
	unsigned char subtype;
	unsigned char id1;
	unsigned char id2;


	int row_id;
		
	/*Recherche du type de device*/	
	if ( DB_MYSQL == 1){
		conn = mysql_connection();	
		result = mysql_select(conn,"SELECT packettype,subtype,id1,id2 FROM devices WHERE dc_id=%d LIMIT 1;", dc_id);
        if (result != NULL)
        {
            int num_fields = mysql_num_fields(result);
        
            while ((row = mysql_fetch_row(result))){
				packettype = stringtohex(row[0]);
				subtype = stringtohex(row[1]);
				id1 = stringtohex(row[2]);
				id2 = stringtohex(row[3]);
			};
		}
        
		mysql_free_result(result);
		mysql_close(conn);
	}
	
	log_DEBUG("[Encode Message] Encoding Message for device: %d, Packettype: %02hhX, subtype: %02hhX, id1: %02hhX, id2: %02hhX ",dc_id,packettype,subtype,id1,id2);

	
	/* ---------------------------------------
    / 0x40 - thermostat 1
    / ---------------------------------------*/
	
	if ( packettype == 0x40)
	{
		
		unsigned char message[12];
		
		message[0]= 0X09;
		message[1]= packettype;
		message[2]= subtype;
		message[3]= 0X00;
		message[4]= id1;
		message[5]= id2;
		message[6]= tp_current;
		message[7]= tp_consigne;

		if (strcmp(demand, "no status") == 0)
		{
			message[8]= 0x00;
		}
		else if ( strcmp(demand, "demand") == 0)
		{
			message[8]= 0x01;
		}
		else if ( strcmp(demand, "no demand") == 0)
		{
			message[8]= 0x02;
		}		
		else if ( strcmp(demand, "initializing") == 0)
		{
			message[8]= 0x03;
		}

		else
		{
			message[8]= 0x00;	
		}
		
		message[9]= 0X09;
		
		
			if(send_message(message) != 0)
			{
				log_ERROR("[Encode Message] Error Sending Message");
				return 1;
			}
	}

	else
	{
		log_ERROR("[Encode Message] Not Suported yet");
		return 1;
	}
    return 1;
}

/*-----------------------------------------------------------------
/		Encode Init message 
/		working for : 0X11 , 0X40
-------------------------------------------------------------------*/

int encode_init_message(int dc_id, char* order)
{

	log_DEBUG("[Encode Message] Starting Encoding Init Message for dc_id: %d, Order: %s ", dc_id,order);
	
	MYSQL *conn;
	MYSQL_RES *result;
	MYSQL_ROW row;
	
	unsigned char packettype;
	unsigned char subtype;
	unsigned char id1;
	unsigned char id2;
	unsigned char id3;
	unsigned char id4;
	unsigned char unitcode;
	unsigned char groupcode;
	unsigned char housecode;
	
	int row_id;
		
	/*Recherche du type de device*/	
	if ( DB_MYSQL == 1){
		conn = mysql_connection();	
		result = mysql_select(conn,"SELECT packettype,subtype,id1,id2,id3,id4,unitcode,groupcode,housecode FROM devices WHERE dc_id=%d LIMIT 1;", dc_id);
        if (result != NULL)
        {
            int num_fields = mysql_num_fields(result);
        
			while ((row = mysql_fetch_row(result))){
				packettype = stringtohex(row[0]);
				subtype = stringtohex(row[1]);
				id1 = stringtohex(row[2]);
				id2 = stringtohex(row[3]);
				id3 = stringtohex(row[4]);
				id4 = stringtohex(row[5]);
				unitcode = stringtohex(row[6]);
				groupcode = stringtohex(row[7]);
				housecode = stringtohex(row[8]);
			};
        }
		mysql_free_result(result);
		mysql_close(conn);
	}
	
	log_DEBUG("[Encode Message] Encoding Message for device: %d, Packettype: %02hhX, subtype: %02hhX, id1: %02hhX, id2: %02hhX , id3: %02hhX, id4:%02hhX, unitcode: %02hhX, groupcode: %02hhX, housecode: %02hhX .",dc_id,packettype,subtype,id1,id2,id3,id4,unitcode,groupcode,housecode);


	if ( strcmp(order,"init") == 0)
	{
		/* ---------------------------------------
		/ 0x11 - Lighting2
		/ ---------------------------------------*/
	
		if ( packettype == 0x11)
		{
		encode_lighting_message(dc_id, "on", 15 );	
		}
		
		/* ---------------------------------------
		/ 0x1A - RFY
		/ ---------------------------------------*/
		
		if ( packettype == 0x1A)
		{
		encode_lighting_message(dc_id, "Program", 0 );	
		}
	
		/* ---------------------------------------
		/ 0x40 - Thermostat1
		/ ---------------------------------------*/

		if ( packettype == 0x40 )
		{
		 encode_thermostat_message( dc_id, 0, 0, "initializing" );
		}
		/* ---------------------------------------
		/ WP - Wiffi Power
		/ ---------------------------------------

		if ( strcmp(packettype,"WP") == 0 )
		{
		 encode_curl_message( dc_id,"init" );
		}
		*/
		log_DEBUG("[Encode Message] End of encode_init_message function");
		return 0;
	}
	else
	{
		log_ERROR("[Encode Message] Order Not Suported yet");
		return 1;
	}

}

/*-----------------------------------------------------------------
/		Encode curl message 
/		working for : 
-------------------------------------------------------------------*/
/*
int encode_curl_message(int dc_id, char* order)
{

	log_DEBUG("Starting Encoding Curl Message for dc_id: %d, Order: %s ", dc_id,order);
	
	MYSQL *conn;
	MYSQL_RES *result;
	MYSQL_ROW row;
	
	unsigned char packettype;
	unsigned char subtype;
	char url[128];
	unsigned char unitcode;
	
	int row_id;
		
	//Recherche du type de device
	if ( DB_MYSQL == 1){
		conn = mysql_connection();	
		result = mysql_select(conn,"SELECT packettype,subtype,address,unitcode FROM devices WHERE dc_id=%d LIMIT 1;", dc_id);
	
		int num_fields = mysql_num_fields(result);
        
			while ((row = mysql_fetch_row(result))){
				packettype = stringtohex(row[0]);
				subtype = stringtohex(row[1]);
				strcpy(m2x_name, row[2]);
				unitcode = stringtohex(row[6]);

			};
		
		mysql_free_result(result);
		mysql_close(conn);
	}
	
	log_DEBUG("Encoding Message for device: %d, Packettype: %02hhX, subtype: %02hhX, id1: %02hhX, id2: %02hhX , id3: %02hhX, id4:%02hhX, unitcode: %02hhX, groupcode: %02hhX, housecode: %02hhX .",dc_id,packettype,subtype,id1,id2,id3,id4,unitcode,groupcode,housecode);


	if ( strcmp(order,"init") == 0)
	{

		
	
		// ---------------------------------------
		// 0x40 - Thermostat1
		// ---------------------------------------

		if ( packettype == 0x40 )
		{
		 encode_thermostat_message( dc_id, 0, 0, "initializing" );
		}
	}
	else
	{
		log_ERROR("Order Not Suported yet");
		return 1;
	}

}
*/
