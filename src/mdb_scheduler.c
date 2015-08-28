/*
 '  mdb_scheduler.c
 '
 '  Created by Jeff on 04/04/15.
 '
 */

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
#include "mdb_encode_messages.h"


int scheduler()
{
	MYSQL *conn;
	MYSQL_RES *result;
	MYSQL_ROW row;
	
	int dc_id;
	char sch_action[10];
    int day = whichday();
	
	/*Recherche des parametres du thermostat*/	
	conn = mysql_connection();
    result = mysql_select(conn,"SELECT dc_id,sch_action FROM scheduler WHERE ((sch_day= %d) OR (sch_day=0)) AND ( CURRENT_TIME <= sch_time) AND (sch_time < TIME(ADDTIME(NOW(),'00:01:00')));",day);
    
    if (result != NULL)
    {
        int num_fields = mysql_num_fields(result);
        
            while (row = mysql_fetch_row(result)){
                dc_id = atoi(row[0]);
                strcpy(sch_action, row[1]);
                encode_lighting_message(dc_id, sch_action, 0);
                log_DEBUG("[Scheduler] Action \"%s\" launched on device dc_id=%d",sch_action,dc_id);
            }
    }
    mysql_free_result(result);
	mysql_close(conn);
    
    return 1;
}