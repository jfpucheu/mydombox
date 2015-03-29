/* mdb_dvn.c */
#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */
#include <time.h>
#include <stdarg.h>
#include <curl/curl.h>

#include "mdb_log.h"

extern	char 	LOG_LEVEL[16];
extern char 	MDB_X_ISS_Key[33];
extern char 	MDB_X_OAPI_Key[33];
extern char 	MDB_DATASOURCE[33];

int post_stream_value(const char *stream,const char * data, ...){
	
	char buffer[2048];
	va_list args;
	va_start(args, data);
	vsprintf (buffer,data, args);
    va_end(args);

	CURL *curl;
	CURLcode res;

	char h_xisskey [64] = "";
	char h_xoapikey [64] = "";
	
	sprintf(h_xisskey,"X-ISS-Key: %s",MDB_X_ISS_Key);
	sprintf(h_xoapikey,"X-OAPI-Key : %s",MDB_X_OAPI_Key);
	
	/* Preparation de l'URL*/
	char url[1024]="";
	sprintf(url,"https://api.orange.com/datavenue/v1/datasources/%s/streams/%s/values",MDB_DATASOURCE,stream);
    log_DEBUG ("ISS POST URL : %s",url);
	log_DEBUG ("ISS POST DATA : %s",buffer);
	//char jsonObj[64]; 
	//sprintf(jsonObj,"[{ \"value\": %d }]",value);
	//printf("%s \n",jsonObj);

	curl = curl_easy_init();

	struct curl_slist *headers = NULL;
	headers = curl_slist_append(headers, "Accept: application/json");
	headers = curl_slist_append(headers, "Content-Type: application/json");
	headers = curl_slist_append(headers, "charsets: utf-8");
	headers = curl_slist_append(headers, h_xisskey);
	headers = curl_slist_append(headers, h_xoapikey);
	
	//enable curl verbose if log level = DEBUG*
	 if ((strcmp(LOG_LEVEL,"DEBUG_SQL") == 0) | (strcmp(LOG_LEVEL,"DEBUG") == 0 )){
		 curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
	}
	
	
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
	curl_easy_setopt(curl, CURLOPT_HTTPHEADER,headers);

	curl_easy_setopt(curl, CURLOPT_URL, url);
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, buffer);
    	
	res = curl_easy_perform(curl);
	        /* Check for errors */
                if(res != CURLE_OK)
					log_DEBUG ("curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
                /* always cleanup */
                curl_easy_cleanup(curl);
}




