/* mdb_tools.c */
#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */
#include <time.h>
#include <stdarg.h>
#include <string.h>

#include "mdb_log.h"
#include "mdb_mysql.h"
#include "mdb_structures.h"

unsigned char stringtohex(char *hexstr)
{
  char *pos = hexstr;
  unsigned char val[1];
  while( *pos ) {
    if( !((pos-hexstr)&1) )
      sscanf(pos,"%02hhX",&val[(pos-hexstr)>>1]);
    ++pos;
  }
  return val[0];
}

unsigned char inttohex(int val)
{
  unsigned char myhex[1];
  myhex[0]= (unsigned char)val;
  return myhex[0];
}


void print_message(unsigned char *message)
{
    int i;	
	for( i=0 ; i <= message[0] ; i++ )
	{
	printf("%02hhX ",message[i]);
	}
printf("\r\n");
}
  

float decode_temperature( char *temperaturehigh, char *temperaturelow){

	float temperature = (( ((temperaturehigh[0] & 0X7F) << 8) | temperaturelow[0]) * 0.1);
	unsigned char temperaturesign = (temperaturehigh[0] >> 7);	
		
	if ( temperaturesign == 0x01){
		temperature = (temperature * (-1)) ;
	}
return temperature;		
}

struct device device_by_id(unsigned char id1,unsigned char id2,unsigned char id3,unsigned char id4, unsigned char unitcode, unsigned char groupcode, unsigned char housecode){

	log_DEBUG("Starting looking for device information with: id1='%02hhX' \n id2='%02hhX' \n id3='%02hhX' \n id4='%02hhX' \n unitcode='%02hhX' \n groupcode='%02hhX' \n housecode='%02hhX' \n",id1,id2,id3,id4,unitcode,groupcode,housecode);

	MYSQL *conn;
	MYSQL_RES *result;
	MYSQL_ROW row;
		
	struct device d;
	
	/*Recherche du device*/	
	conn = mysql_connection();
	result = mysql_select(conn,"SELECT dc_id,dc_name,enable,m2x_status,m2x_name FROM devices WHERE id1='%02hhX' AND id2='%02hhX' AND id3='%02hhX' AND id4='%02hhX' AND unitcode='%02hhX' AND groupcode='%02hhX' AND housecode='%02hhX' LIMIT 1", id1,id2,id3,id4,unitcode,groupcode,housecode);
	
	int num_fields = mysql_num_fields(result);

	/* If num fields is different than 0, return the structure with device information */
	
	if ( num_fields != 0 )
	{
		while (row = mysql_fetch_row(result)){
			d.dc_id = atoi(row[0]);
			strcpy(d.dc_name,row[1]);
			d.enable = atoi(row[2]);
			d.m2x_status = atoi(row[3]);
			strcpy(d.m2x_name, row[4]);
		};
	}
	else /* return dc_id=-1 , no device founded */
	{
		d.dc_id = -1;
	}
	
	mysql_free_result(result);
	mysql_close(conn);	

return d;
}

