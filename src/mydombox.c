#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <my_global.h> /* Mysql lib */
#include <mysql.h> 	/* Mysql lib */

#include "mdb_config_reader.h"
#include "mdb_log.h"
#include "mdb_mysql.h"
#include "mdb_rfxtrx433.h"
#include "mdb_enocean_usb300.h"
#include "mdb_decode_enocean_messages.h"
#include "mdb_rpidom.h"
#include "mdb_thermostat.h"
#include "mdb_soapserver.h"
#include "mdb_scheduler.h"
#include "mdb_tools.h"


MYSQL *conn;
MYSQL_RES *result;

extern 	int 	MODULE_RPIDOM;
extern 	int 	MODULE_SOAP;
extern	char 	LOG_LEVEL[16];
extern 	char 	PORT_RFXTRX433[32];
extern 	char 	PORT_ENOUSB300[32];

int 	RECORD = 0;

int main(int argc, char *argv[])
{

if ( argc < 2 ) /* argc should be 2 for correct execution */
{
	printf( "Missing config file path argument \n" );
}
   
if(read_config_file(argv[1]))
{
	printf("Error Loading Configuration File\n");
	printf("Exiting Mydombox .... By !\n");
	exit(1);
}


log_INFO("--------- Starting Mydombox Server ---------");
log_INFO("MySQL client version: %s", mysql_get_client_info());
log_INFO("Loglevel: %s",LOG_LEVEL);
log_INFO("Learn Mode: %d",RECORD);

	conn = mysql_connection();
	result = mysql_select(conn,"SELECT * FROM devices;");
	mysql_free_result(result);
	mysql_close(conn);


if ( file_exists(PORT_RFXTRX433) ){
    // On crée un thread
    pthread_t thread_rfxtrx433;
    // Permet d'exécuter le fonction thread_rfxtrx433 en parallèle
    pthread_create(&thread_rfxtrx433, NULL, rfxtrx433, NULL);
	log_INFO("Module RFXTRX433 Detected & Started");
}

sleep(5);

if ( file_exists(PORT_ENOUSB300) ){
    // On crée un thread
    pthread_t thread_enusb300;
    // Permet d'exécuter le fonction thread_enusb300 en parallèle
    pthread_create(&thread_enusb300, NULL, enusb300, NULL);
    log_INFO("Module USB300 Detected & Started");
}
    
    
sleep(10);

if ( MODULE_SOAP == 1){
    // On crée un thread
    pthread_t thread_soapserver;
    // Permet d'exécuter le fonction thread_soapserver en parallèle
    pthread_create(&thread_soapserver, NULL, soapserver, NULL);
	log_INFO("Module SOAP Started");
}

sleep(5);
if ( MODULE_RPIDOM == 1){
    // On crée un thread
    pthread_t thread_rpidom;
    // Permet d'exécuter le fonction thread_rpidom en parallèle
    pthread_create(&thread_rpidom, NULL, rpidom, NULL);
	log_INFO("Module RPIDOM Started");
}

while(1){
	read_config_file(argv[1]);
    scheduler();
	thermostat();
	sleep (60);
}

return 0;
}
