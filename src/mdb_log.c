/* mdb_decode_messages.c */
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

//external variables
extern	char 	LOG_LEVEL[16];
extern 	char 	LOG_FILE_PATH[1024];

//functions variables
char 			LOG_FILE[1048];
char 			datelog[16];


void log_DEBUG_SQL(const char * message, ... ){
	
	char buffer[2048];
	va_list args;
	va_start(args, message);
	vsprintf (buffer,message, args);
    va_end(args);
	
	FILE* fichier = NULL;
	
	char datetime[128];
    time_t temps;
    struct tm date;
	
    time(&temps);
    date=*localtime(&temps);
 
    strftime(datetime, 128, "%Y-%m-%d %X", &date);	
	strftime(datelog, 16, "%Y-%m-%d",&date);
	sprintf(LOG_FILE, "%s/mydombox-%s.log", LOG_FILE_PATH, datelog);

	
	
    fichier = fopen(LOG_FILE, "a");
  
    if (fichier != NULL){
		if ((strcmp(LOG_LEVEL,"DEBUG_SQL") == 0) | (strcmp(LOG_LEVEL,"DEBUG") == 0) | (strcmp(LOG_LEVEL,"ERROR") == 0) | (strcmp(LOG_LEVEL,"INFO") == 0)){
			if ( strcmp(LOG_LEVEL,"DEBUG_SQL") == 0 ){
				fprintf(fichier, "[%s][DEBUG_SQL]: %s\n", datetime,buffer);
			}
		}
		else{	
			fprintf(fichier, "[%s][ERROR]: %s\n", datetime,"Wrong LOG LEVEL, please check config");			
		}
		fclose(fichier);
	}
	else{
		printf("Error Writing Log File: %s \n", LOG_FILE);
	}
}	

void log_DEBUG(const char * message, ... ){
	
	char buffer[2048];
	va_list args;
	va_start(args, message);
	vsprintf (buffer,message, args);
    va_end(args);

	FILE* fichier = NULL;
	
	char datetime[128];
    time_t temps;
    struct tm date;
 
    time(&temps);
    date=*localtime(&temps);
 
    strftime(datetime, 128, "%Y-%m-%d %X", &date);	
	strftime(datelog, 16, "%Y-%m-%d",&date);
	sprintf(LOG_FILE, "%s/mydombox-%s.log", LOG_FILE_PATH, datelog);
	
    fichier = fopen(LOG_FILE, "a");
  
    if (fichier != NULL){
		if ((strcmp(LOG_LEVEL,"DEBUG_SQL") == 0) | (strcmp(LOG_LEVEL,"DEBUG") == 0) | (strcmp(LOG_LEVEL,"ERROR") == 0) | (strcmp(LOG_LEVEL,"INFO") == 0)){
			if ((strcmp(LOG_LEVEL,"DEBUG_SQL") == 0) | (strcmp(LOG_LEVEL,"DEBUG") == 0 )){
				fprintf(fichier, "[%s][DEBUG]: %s\n", datetime,buffer);
			}
		}
		else{	
			fprintf(fichier, "[%s][ERROR]: %s\n", datetime,"Wrong LOG LEVEL, please check config");			
		}
		fclose(fichier);
	}
	else{
		printf("Error Writing Log File: %s \n", LOG_FILE);
	}
}	

void log_ERROR(const char * message, ... ){

	char buffer[2048];
	va_list args; //
	va_start(args, message); //
	vsprintf (buffer,message, args);
    va_end(args);

	FILE* fichier = NULL;
	
	char datetime[128];
    time_t temps;
    struct tm date;
 
    time(&temps);
    date=*localtime(&temps);
 
    strftime(datetime, 128, "%Y-%m-%d %X", &date);	
	strftime(datelog, 16, "%Y-%m-%d",&date);
	sprintf(LOG_FILE, "%s/mydombox-%s.log", LOG_FILE_PATH, datelog);
	
    fichier = fopen(LOG_FILE, "a");
  
    if (fichier != NULL){
		if ((strcmp(LOG_LEVEL,"DEBUG_SQL") == 0) | (strcmp(LOG_LEVEL,"DEBUG") == 0) | (strcmp(LOG_LEVEL,"ERROR") == 0) | (strcmp(LOG_LEVEL,"INFO") == 0)){
			if ((strcmp(LOG_LEVEL,"DEBUG_SQL") == 0) | (strcmp(LOG_LEVEL,"ERROR") == 0) | (strcmp(LOG_LEVEL,"DEBUG") == 0)){
				fprintf(fichier, "[%s][ERROR]: %s\n", datetime,buffer);
			}
		}
		else{	
			fprintf(fichier, "[%s][ERROR]: %s\n", datetime,"Wrong LOG LEVEL, please check config");			
		}
		fclose(fichier);
	}
	else{
		printf("Error Writing Log File: %s \n", LOG_FILE);
	}
}

void log_INFO(const char * message, ... ){

	char buffer[2048];
	va_list args; //
	va_start(args, message); //
	vsprintf (buffer,message, args);
    va_end(args);

	FILE* fichier = NULL;
	
	char datetime[128];
    time_t temps;
    struct tm date;
 
    time(&temps);
    date=*localtime(&temps);
 
    strftime(datetime, 128, "%Y-%m-%d %X", &date);	
	strftime(datelog, 16, "%Y-%m-%d",&date);
	sprintf(LOG_FILE, "%s/mydombox-%s.log", LOG_FILE_PATH, datelog);
	
    fichier = fopen(LOG_FILE, "a");
  
    if (fichier != NULL){
		if ((strcmp(LOG_LEVEL,"DEBUG_SQL") == 0) | (strcmp(LOG_LEVEL,"DEBUG") == 0) | (strcmp(LOG_LEVEL,"ERROR") == 0) | (strcmp(LOG_LEVEL,"INFO") == 0)){
			if ((strcmp(LOG_LEVEL,"DEBUG_SQL") == 0) | (strcmp(LOG_LEVEL,"DEBUG") == 0) | (strcmp(LOG_LEVEL,"ERROR") == 0) | (strcmp(LOG_LEVEL,"INFO") == 0)){
				fprintf(fichier, "[%s][INFO]: %s\n", datetime,buffer);
			}
		}
		else{	
			fprintf(fichier, "[%s][ERROR]: %s\n", datetime,"Wrong LOG LEVEL, please check config");			
		}
		fclose(fichier);
	}
		else{
		printf("Error Writing Log File: %s \n", LOG_FILE);
	}
	
}