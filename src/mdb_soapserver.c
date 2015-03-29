//
//  mdb_soapserver.c
//  
//
//  Created by Jeff on 25/06/13.
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

#include "lib/gsoap/soapH.h"
#include "lib/gsoap/mydombox.nsmap" 

#include "mdb_log.h"
#include "mdb_tools.h"
#include "mdb_mysql.h"
#include "mdb_encode_messages.h"

extern int PORT_SOAP;

int __ns1__getLightingStatus(
	struct soap *soap,
    	// input parameters:
    	struct _ns1__getLightingStatus*		getLightingStatus,
    	// output parameters:
    	struct _ns1__getLightingStatusResponse* 	getLightingStatusResponse)
{
	       //Traitement reponde
		

	
	MYSQL *conn;
	MYSQL_RES *result;
	MYSQL_ROW row;

	int dc_id=getLightingStatus->DeviceID;
	
	int res_dc_id=0;
	char res_state[16];
	int res_dim=0; 

	log_DEBUG("Get Ligting informations for device: dc_id: %d \n", dc_id);
	
	/*Recherche du type de device*/	
	conn = mysql_connection();	
	result = mysql_select(conn,"SELECT dc_id,device_mode,dim_level FROM state WHERE dc_id=%d LIMIT 1;", dc_id);
	log_DEBUG_SQL("SELECT dc_id,device_mode,dim_level FROM state WHERE dc_id=%d LIMIT 1;", dc_id);
	
	int num_fields = mysql_num_fields(result);
        
        while ((row = mysql_fetch_row(result))){
			res_dc_id = atoi(row[0]);
			strcpy(res_state,row[1]);
			res_dim = atoi(row[2]);
        };
		
    mysql_free_result(result);
	mysql_close(conn);
	
	log_DEBUG("***************%d,%s,%d",res_dc_id,res_state,res_dim);
	/* allocate response */
        getLightingStatusResponse->State = (char*)soap_malloc(soap,16);
		getLightingStatusResponse->Dim = (int*)soap_malloc(soap,1);

		if ( res_dc_id != 0)
        {
                getLightingStatusResponse->DeviceID = res_dc_id;
                sprintf( getLightingStatusResponse->State,res_state);
                *getLightingStatusResponse->Dim =res_dim;
        }

        else
        {
                char *s = (char*)soap_malloc(soap, 1024);
                sprintf(s, "<error> Oups ! Unexpected error </error>");
                return soap_sender_fault(soap, "ER001 : Error trying to get device informations", s);
        }
return SOAP_OK;
}	

int __ns1__setLightingStatus(
    	struct soap *soap,
    	// input parameters:
    	struct _ns1__setLightingStatus*     setLightingStatus,
    	// output parameters:
    	struct _ns1__setLightingStatusResponse* setLightingStatusResponse)
{
		int dc_id=setLightingStatus->DeviceID;
		char state[16];
		strcpy(state,setLightingStatus->State);
		int dim = 0;
		
		// Verification des parametres optionnel
		if (setLightingStatus->Dim){
			dim = *setLightingStatus->Dim ;
		}

		//transformation de la requette et envoi
		if (encode_lighting_message(dc_id, state, dim) == 0)
		{
			//sleep(1);
			//Traitement reponse
		
			log_DEBUG("set Lighting informations for device: dc_id: %d \n", dc_id);
	
			MYSQL *conn;
			MYSQL_RES *result;
			MYSQL_ROW row;

			int res_dc_id=0;
			char res_state[16];
			int res_dim=0; 
		
			/*Recherche du type de device*/	
			conn = mysql_connection();	
			result = mysql_select(conn,"SELECT dc_id,device_mode,dim_level FROM state WHERE dc_id=%d LIMIT 1;", dc_id);
	
			int num_fields = mysql_num_fields(result);
        
			while ((row = mysql_fetch_row(result))){
				res_dc_id = atoi(row[0]);
				strcpy(res_state,row[1]);
				res_dim = atoi(row[2]);
			};
		
			mysql_free_result(result);
			mysql_close(conn);
		
			/* allocate response */
			setLightingStatusResponse->State = (char*)soap_malloc(soap,16);
			setLightingStatusResponse->Dim = (int*)soap_malloc(soap,1);

			if ( res_dc_id != 0)
			{
                setLightingStatusResponse->DeviceID = res_dc_id;
                sprintf( setLightingStatusResponse->State,res_state);
                *setLightingStatusResponse->Dim =res_dim;
			}

			else
			{
                char *s = (char*)soap_malloc(soap, 1024);
                sprintf(s, "<error> Oups ! Unexpected error </error>");
                return soap_sender_fault(soap, "ER002 : Error trying to set device informations", s);
			}			
		return SOAP_OK;
		}
		else
		{
		char *s = (char*)soap_malloc(soap, 1024);
        sprintf(s, "<error> Oups ! Unexpected error </error>");
        return soap_sender_fault(soap, "ER002 : Error trying to set device informations", s);
		}
		
}


int __ns1__initDevice(
	struct soap *soap,
    struct _ns1__initDevice*            initDevice,
    struct _ns1__initDeviceResponse*    initDeviceResponse)
{

		int dc_id=initDevice->DeviceID;
		char order[16];
		strcpy(order,initDevice->Order);

		//transformation de la requette et envoi
		if (encode_init_message(dc_id, order) == 0)
		{
			//sleep(1);
			//Traitement reponse
		
			log_DEBUG("Set Init informations for device: dc_id: %d \n", dc_id);
	
			MYSQL *conn;
			MYSQL_RES *result;
			MYSQL_ROW row;

			int res_dc_id=0;
		
			/*Recherche du type de device*/	
			conn = mysql_connection();	
			result = mysql_select(conn,"SELECT dc_id from devices WHERE dc_id=%d LIMIT 1;", dc_id);
	
			int num_fields = mysql_num_fields(result);
        
			while ((row = mysql_fetch_row(result))){
				res_dc_id = atoi(row[0]);
			};
		
			mysql_free_result(result);
			mysql_close(conn);
		
			/* allocate response */
			initDeviceResponse->Order = (char*)soap_malloc(soap,16);

			if ( res_dc_id != 0)
			{
                initDeviceResponse->DeviceID = res_dc_id;
                sprintf( initDeviceResponse->Order,order);
			}

			else
			{
                char *s = (char*)soap_malloc(soap, 1024);
                sprintf(s, "<error> Oups ! Unexpected error </error>");
                return soap_sender_fault(soap, "ER003 : Error trying to find device informations", s);
			}			
		return SOAP_OK;
		}
		else
		{
		char *s = (char*)soap_malloc(soap, 1024);
        sprintf(s, "<error> Oups ! Unexpected error </error>");
        return soap_sender_fault(soap, "ER002 : Error trying to set init device informations", s);
		}
}

/* TO BE IMPLEMENTED
int http_get(struct soap *soap)
{
   FILE *fd = NULL;
   char *s = strchr(soap->path, '?');
   if (!s || strcmp(s, "?wsdl"))
      return SOAP_GET_METHOD;
   fd = fopen("mydombox.wsdl", "rb"); // open WSDL file to copy
   if (!fd)
      return 404; // return HTTP not found error
   soap->http_content = "text/xml"; // HTTP header with text/xml content
   soap_response(soap, SOAP_FILE);
   for (;;)
   {
      size_t r = fread(soap->tmpbuf, 1, sizeof(soap->tmpbuf), fd);
      if (!r)
         break;
      if (soap_send_raw(soap, soap->tmpbuf, r))
         break; // can't send, but little we can do about that
   }
   fclose(fd);
   soap_end_send(soap);
   return SOAP_OK;
} 
*/

void soapserver() {
    int m, s;
    struct soap soap;
 
    soap_init(&soap);
    m = soap_bind(&soap, NULL, PORT_SOAP, 100);
    if (m < 0) {
        soap_print_fault(&soap, stderr);
        exit(-1);
    }
	log_INFO("Socket connection successful");
    while (1) {
        s = soap_accept(&soap);
        if (s < 0) {
            soap_print_fault(&soap, stderr);
            exit(-1);
        }
        soap_serve(&soap);
        soap_end(&soap);
    }
 
}