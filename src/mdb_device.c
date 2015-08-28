//
//  mdb_device.c
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
#include "mdb_tools.h"


struct sDevice myDevice(int int_id,unsigned char id1,unsigned char id2,unsigned char id3,unsigned char id4,unsigned char unitcode,unsigned char groupcode,unsigned char housecode){
    
    sDevice* device
    device->dc_id = 0;

	MYSQL *conn;
	MYSQL_RES *result;
	MYSQL_ROW row;

    
    conn = mysql_connection();
    result = mysql_select(conn,"SELECT (dc_id,packettype,subtype,int_id,id1,id2,id3,id4,unitcode,com; from devices (dc_id,packettype,subtype,int_id,id1,id2,id3,id4,unitcode,com;",packettype,subtype,int_id,id1,id2,id3,id4,unitcode,com);
	
    int num_fields = mysql_num_fields(result);
    if (num_fields != 0) {
        
        while ((row = mysql_fetch_row(result))){
            device->dc_id       = row[0];
            device->packettype  = row[1];
            device->subtype     = row[2];
            device->int_id      = (int)row[3];
            device->address     = row[4];
            device->id1  		= row[5];
            device->id2 		= row[6];
            device->id3 		= row[7];
            device->id4 		= row[8];
            device->unitcode 	= row[9];
            device->groupcode 	= row[10];
            device->housecode 	= row[11];
            device->enable 		= row[12];
        }
    }
    
    return device;
}

struct sDevice myDevice addDevice(int int_id,unsigned char id1,unsigned char id2,unsigned char id3,unsigned char id4,unsigned char unitcode,unsigned char groupcode,unsigned char housecode){
    
    sDevice* device = myDevice(int_id,id1,id1,id3,id4,unitcode,groupcode,housecode);
    
    if (device->dc_id = 0 & record = 1) {
        //Insert device
        device = myDevice(int_id,id1,id1,id3,id4,unitcode,groupcode,housecode);
        return device->dc_id;
    } else {
        return 0;
    }
    
}

int dc_id = device->dc_id;

if (dc_id = 0) dc_id = addDevice();

if (dc_id != 0){
    //insert data
}







