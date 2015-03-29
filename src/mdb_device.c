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
#include "mdb_decode_messages.h"
#include "mdb_encode_messages.h"
#include "mdb_tools.h"



/* 
is_device_exit()
	- return device ID if exit
	- return 0 if device not existing
*/

int is_device_exit(packettype,subtype,int_id,id1,id2,id3,id4,unitcode,com)
{

int device_id = 0;

MYSQL *conn;
MYSQL_RES *result;
MYSQL_ROW row;

	
/*Recherche du type de recepteur du thermostat*/	
conn = mysql_connection();
result = mysql_select(conn,"select * from devices (dc_id,last_update,packettype,subtype,int_id,id1,id2,id3,id4,unitcode,com;",packettype,subtype,int_id,id1,id2,id3,id4,unitcode,com);
	
int num_fields = mysql_num_fields(result);
	
	while ((row = mysql_fetch_row(result))){
		subtype = stringtohex(row[0]);
	};
	
mysql_free_result(result);
mysql_close(conn);

return device_id;
}


/* 
is_device_exit()
	- return device ID if exit
	- return 0 if device not existing
*/

	// MYSQL INSERTION
	if ( DB_MYSQL == 1){
					
		mysql_insert("INSERT IGNORE INTO devices (dc_id,last_update,packettype,subtype,int_id,id1,id2,id3,id4,unitcode,com) SELECT MAX(dc_id)+1,NOW(),'%02hhX','%02hhX',1,'%02hhX','%02hhX','%02hhX','%02hhX',%d,'tx' FROM devices ON DUPLICATE KEY UPDATE last_update=NOW();\
					
					",packettype,subtype,id1,id2,id3,id4,unitcode,id1,id2,id3,id4,unitcode,cmnd_text,level,rssi,cmnd_text,level,rssi);
	}
