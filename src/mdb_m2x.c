/* mdb_decode_messages.c */
#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */
#include <time.h>
#include <stdarg.h>

#include "lib/m2x-c/m2x.h"
#include "lib/m2x-c/feed.h"

#include "mdb_log.h"

extern char 	MDB_KEY[32];
extern char 	MDB_ID[32];



int post_M2X(const char * stream_name,const char * data, ...){
	
	char buffer[2048];
	va_list args;
	va_start(args, data);
	vsprintf (buffer,data, args);
    va_end(args);
	
	m2x_context *ctx = NULL;


	/*  sprintf(buf, "{\"value\":\"%d\"}", rand());*/
	  ctx = m2x_open(MDB_KEY);
	  if (m2x_feed_update_stream(ctx, MDB_ID, stream_name, buffer, NULL) == 0)
		{
			log_DEBUG("Feed Stream %s updated with data: %s", stream_name,buffer);
		}
	  m2x_close(ctx);

	return 0;
}




