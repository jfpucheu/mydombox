/* mdb_decode_messages.c */
#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */
#include <time.h>
#include <stdarg.h>
#include <my_global.h> /* Mysql lib */
#include <mysql.h> 	/* Mysql lib */

#include "mdb_log.h"

extern char 	HOSTNAME[32];
extern int 		PORT;
extern char 	LOGIN[16];
extern char 	PASSWORD[16];
extern char 	DATABASE[16];

MYSQL* mysql_connection(void){

    //Déclaration des pointeurs de structure
    MYSQL *conn;
	conn = mysql_init(NULL);
    
	if (conn == NULL) {
		log_ERROR("Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
        exit(0);
	}
	if (mysql_real_connect(conn, HOSTNAME, LOGIN, PASSWORD, DATABASE, PORT, NULL, CLIENT_MULTI_STATEMENTS) == NULL) {
		log_ERROR("Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
        exit(0);
	}
	else {
		return conn;
	}
}

int mysql_insert(const char * query, ...){
	
	char buffer[2048];
	va_list args;
	va_start(args, query);
	vsprintf (buffer,query, args);
    va_end(args);
	
	//Log de la requette en DEBUG_SQL
	log_DEBUG_SQL("%s",buffer);

	MYSQL *conn;
	conn = mysql_connection();

	if (mysql_query(conn, buffer)) {
		log_ERROR("Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
		mysql_close(conn);
		return 1;
	}
	mysql_close(conn);
    mysql_library_end();
	return 0;
}

MYSQL_RES* mysql_select(MYSQL* conn,const char * query, ...){
	
	char buffer[2048];
	va_list args;
	va_start(args, query);
	vsprintf (buffer,query, args);
    va_end(args);
    
	//Log de la requette en DEBUG_SQL
	log_DEBUG_SQL("%s",buffer);
	
    //Déclaration des pointeurs de structure
    MYSQL_RES *result;
    
	if (mysql_query(conn, buffer)) {
		log_ERROR("Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
		return NULL;
    }
    else {
        result = mysql_store_result(conn);
		return result;
	}
}


void mysql_printf_select(const char * query, ...){
	
	char buffer[2048];
	va_list args;
	va_start(args, query);
	vsprintf (buffer,query, args);
    va_end(args);
    
    //Déclaration des pointeurs de structure
    MYSQL *conn;
    MYSQL_RES *result;
    MYSQL_ROW row;
    
    int num_fields;
    int i;
    
	conn = mysql_init(NULL);
    
	if (conn == NULL) {
		log_ERROR("Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
	}
	if (mysql_real_connect(conn, HOSTNAME, LOGIN, PASSWORD, DATABASE, PORT, NULL, CLIENT_MULTI_STATEMENTS) == NULL) {
		log_ERROR("Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
	}
	if (mysql_query(conn, buffer)) {
		log_ERROR("Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
    }
    else {
        result = mysql_store_result(conn);
        num_fields = mysql_num_fields(result);
        
        while ((row = mysql_fetch_row(result)))
        {
            //for(i = 0; i < num_fields; i++)
            //{
            //    printf("%s ", row[i]);
            //}
            //printf("\n");
			printf("%s \n", row[0]);
        };
    }
    mysql_free_result(result);
	mysql_close(conn);
    mysql_library_end();
}


