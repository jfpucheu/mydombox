#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mdb_log.h"

#define DELIM '='
#define ENDLIM ';'

//variables fichier de conf
char 	LOG_FILE_PATH[1024] = "";
char 	LOG_LEVEL[16] = "";
int 	MYSQL;
char 	HOSTNAME[32] = "";
int 	PORT;
char 	LOGIN[16]= "";
char 	PASSWORD[16] = "";
char 	DATABASE[16] = "";
int 	MODULE_SOAP;
char 	PORT_RFXTRX433[32]="";
char 	PORT_ENOUSB300[32]="";
int 	PORT_SOAP;
int 	MODULE_RPIDOM;
char 	PORT_RPIDOM[32]="";
int 	RPIDOM_TELE1_TYPE;
int 	RPIDOM_TELE2_TYPE;
int 	RPIDOM_1WIRE;
int 	MDB_CLOUD;
char 	MDB_KEY[64] = "";
char 	MDB_ID[64] = "";
char 	MDB_X_ISS_Key[33] = "";
char 	MDB_X_OAPI_Key[33] = "";
char 	MDB_DATASOURCE[33] = "";


// Add new variables here if necessary


int variable_detection(char buffer[512])
{
int i=0;
int j=0;
char name[512]={'\0'};
char value[512]={'\0'};
int int_value=0;

	while( buffer[i] != DELIM )
	{
		name[i]=buffer[i];
		i++;
	}
i++;

	while( buffer[i] != ENDLIM )
	{
		value[j]=buffer[i];
		i++;
		j++;
	}
	
	if (!strcmp(name,"LOG_FILE_PATH")){
		strcpy(LOG_FILE_PATH,value);
	}
	else if (!strcmp(name,"LOG_LEVEL")){
		strcpy(LOG_LEVEL,value);
		
	}
	else if (!strcmp(name,"MYSQL")){
		MYSQL = atoi(value);
	}
        else if (!strcmp(name,"HOSTNAME")){
	        strcpy(HOSTNAME,value);
	}
	else if (!strcmp(name,"PORT")){
                PORT = atoi(value);
    }
	else if (!strcmp(name,"LOGIN")){
                strcpy(LOGIN,value);
	}
	else if (!strcmp(name,"PASSWORD")){
                strcpy(PASSWORD,value);
    }
    else if (!strcmp(name,"DATABASE")){
                strcpy(DATABASE,value);
    }
    else if (!strcmp(name,"PORT_RFXTRX433")){
                strcpy(PORT_RFXTRX433,value);
    }
    else if (!strcmp(name,"PORT_ENOUSB300")){
        strcpy(PORT_ENOUSB300,value);
    }
	else if (!strcmp(name,"MODULE_SOAP")){
                MODULE_SOAP = atoi(value);
    }
	else if (!strcmp(name,"PORT_SOAP")){
                PORT_SOAP = atoi(value);
	}
	else if (!strcmp(name,"MODULE_RPIDOM")){
                MODULE_RPIDOM = atoi(value);
	}
	else if (!strcmp(name,"PORT_RPIDOM")){
                strcpy(PORT_RPIDOM,value);
	}
	else if (!strcmp(name,"RPIDOM_TELE1_TYPE")){
                 RPIDOM_TELE1_TYPE = atoi(value);
	}
	else if (!strcmp(name,"RPIDOM_TELE2_TYPE")){
                 RPIDOM_TELE2_TYPE = atoi(value);
	}
	else if (!strcmp(name,"RPIDOM_1WIRE")){
                 RPIDOM_1WIRE = atoi(value);
	}
	else if (!strcmp(name,"MDB_CLOUD")){
                MDB_CLOUD = atoi(value);
    }
	else if (!strcmp(name,"MDB_KEY")){
                strcpy(MDB_KEY,value);
    }
	else if (!strcmp(name,"MDB_ID")){
                strcpy(MDB_ID,value);
    }
	else if (!strcmp(name,"MDB_X_ISS_Key")){
                strcpy(MDB_X_ISS_Key,value);
    }
	else if (!strcmp(name,"MDB_X_OAPI_Key")){
                strcpy(MDB_X_OAPI_Key,value);
    }
	else if (!strcmp(name,"MDB_DATASOURCE")){
                strcpy(MDB_DATASOURCE,value);
    }
	else{
		log_ERROR("Parameter : \"%s\" not yet supported by mydombox",name);
	}
	
	/*
	detecting if it is a char or int
	if (( value[0] != '"')&&(value[0] >= '0' && value[0] <= '9'))
	{
	int_value = atoi (value );
	printf("int %s= %d \n", name,int_value);

	}
	else
	{
	printf("char %s = %s \n", name,value);
	}
	*/

return 0;
}

   
     
int read_config_file(char CONFIGFILE[1024])
{

FILE *fic = NULL;
int nb_lignes;
char line[512]={'\0'};

fic=fopen (CONFIGFILE,"r");

	if(fic==NULL)
	{
		//printf("Probleme a l'ouverture du fichier de configuration\n");
		return 1;
	}

// compter et afficher les lignes du fichier
nb_lignes = 0;

while(fgets(line, 512, fic) != NULL)	
{
	if( (line[0] != '#') && (line[0] != '\n'))
	{
		variable_detection(line);
	}
nb_lignes++;
}
		log_INFO("\n--------- Loading Mydombox Server configuration ---------");
		log_DEBUG("LOG_FILE_PATH = %s", LOG_FILE_PATH);
		log_DEBUG("LOG_LEVEL = %s", 	LOG_LEVEL);
        log_DEBUG("MYSQL = %d",         MYSQL);
        log_DEBUG("HOSTNAME = %s",      HOSTNAME);
        log_DEBUG("PORT = %d",          PORT);
        log_DEBUG("LOGIN = %s",         LOGIN);
        log_DEBUG("PASSWORD = %s",      PASSWORD);
        log_DEBUG("DATABASE = %s", 		DATABASE);
        log_DEBUG("PORT_RFXTRX433 = %s",PORT_RFXTRX433);
        log_DEBUG("PORT_ENOUSB300 = %s",PORT_ENOUSB300);
        log_DEBUG("MODULE_SOAP = %d",   MODULE_SOAP);
		log_DEBUG("PORT_SOAP = %d",		PORT_SOAP);
        log_DEBUG("MODULE_RPIDOM = %d",   MODULE_RPIDOM);
        log_DEBUG("PORT_RPIDOM = %s",	PORT_RPIDOM);
		log_DEBUG("RPIDOM_TELE1_TYPE = %d",		RPIDOM_TELE1_TYPE);
		log_DEBUG("RPIDOM_TELE2_TYPE = %d",		RPIDOM_TELE2_TYPE);
		log_DEBUG("RPIDOM_1WIRE = %d",		RPIDOM_1WIRE);
		log_DEBUG("MDB_CLOUD = %d",   MDB_CLOUD);
        log_DEBUG("MDB_KEY = %s",	MDB_KEY);
        log_DEBUG("MDB_ID = %s",	MDB_ID);
        log_DEBUG("MDB_X_ISS_Key = %s",	MDB_X_ISS_Key);
        log_DEBUG("MDB_X_OAPI_Key = %s",	MDB_X_OAPI_Key);
        log_DEBUG("MDB_DATASOURCE = %s",	MDB_DATASOURCE);
		log_DEBUG("--------------------------------------------------------\n");

fclose(fic);
return 0;	
}
