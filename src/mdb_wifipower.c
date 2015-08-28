/* mdb_wifipower.c */

#include <stdio.h>   /* Standard input/output definitions */
#include <stdlib.h>
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */

#include "mdb_log.h"
#include <curl/curl.h>
#include "mdb_mysql.h"
#include "mdb_decode_messages.h"



int encode_wifipower_message(char url[255], int unitcode, char order[8])
{
        unsigned long len;
        char  urlmessage[300];
        char buffer[256];

        //detection du slash en fin d'URL
        len = strlen(url);

        if( url[len-1] != '/'){
                sprintf(buffer,"%s/",url);
        }
        else
        {
                sprintf(buffer,"%s",url);
        }

        if ( strcmp(order,"switch")==0 ){
                sprintf(urlmessage, "%sS%d", buffer,unitcode);
        }
        else if (strcmp(order,"off")==0){
                sprintf(urlmessage, "%sR%d0", buffer,unitcode);
        }
        else if (strcmp(order,"on")==0){
                sprintf(urlmessage, "%sR%d1", buffer,unitcode);
        }
        else if (strcmp(order,"status")==0){
                sprintf(urlmessage, "%sQ", url,unitcode);
        }
        else
        {
                return 1;
        }

        printf("url encodee: %s \n",urlmessage );

        return 0;
}

main()
{
encode_wifipower_message("http://192.168.64.10:8080",2,"on");
encode_wifipower_message("http://192.168.64.10:8080/",1,"off");
encode_wifipower_message("http://192.168.64.10:8080",2,"switch");
encode_wifipower_message("http://192.168.64.10:8080",2,"swh");
return 0;

}

	CURL *curl;
	CURLcode res;
 
	curl = curl_easy_init();
  
	if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, "http://example.com");
    
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
 
    /* Perform the request, res will get the return code */ 
    res = curl_easy_perform(curl);
    /* Check for errors */ 
		if(res != CURLE_OK)
		  fprintf(stderr, "curl_easy_perform() failed: %s\n",
				  curl_easy_strerror(res));
	 
		/* always cleanup */ 
		curl_easy_cleanup(curl);
	}
  return 0;








Switch un relais http://192.168.0.190:2000/Sn
Avec « n » variant de 1 à 8 suivant le
Positionner OFF un relais http://192.168.0.190:2000/Rn0 produit
Positionner ON un relais http://192.168.0.190:2000/Rn1
Lire statut des relais http://192.168.0.190:2000/Q
RESET du produit http://192.168.0.190:2000/ZZ55















/*
* 'open_port()' - Open serial port 1.
*
* Returns the file descriptor on success or -1 on error.
*/
int serial_port_open(void)
{
	log_INFO("Starting Listening on %s", PORT_RFXTRX433);
	
	fdrfxtrx = open(PORT_RFXTRX433, O_RDWR | O_APPEND | O_NOCTTY | O_RSYNC | O_SYNC );

	if (fdrfxtrx == -1)
	{
	/*
	* Could not open the port.
	*/
		perror("open_port: Unable to open Serial Port - ");
		log_ERROR("open_port: Unable to open Serial Port");
		exit(1);

	}

	//RECONFIGURATION
	/* get the current options */
    tcgetattr(fdrfxtrx, &oldconfig);
	bzero(&newconfig, sizeof(newconfig));
	
	newconfig.c_cc[VMIN]  = 1;
    newconfig.c_cc[VTIME] = 0;
	
	/* Enable the receiver and set local mode */
	newconfig.c_cflag   = ( CS8 | CREAD | CLOCAL );
	
	/* vitesse du port*/
	cfsetispeed(&newconfig, BAUDRATE); 
    cfsetospeed(&newconfig, BAUDRATE);
	
	/* clear buffer serial*/
	tcflush(fdrfxtrx, TCIOFLUSH); 
	
    /* set the options */
	tcsetattr(fdrfxtrx, TCSANOW, &newconfig);
	//FIN RECONFIGURATION
	

return (fdrfxtrx);
}	

int read_rfxtrx(void)
{
	int res,i=1;
	char in[1],size[1];
	char buffer[255]={'\0'}; /* Input buffer */
	
	res = read(fdrfxtrx,size,1);

        if (res>0)
        {
			buffer[0]=size[0];
			
			while (i <= size[0])
			{
				res = read(fdrfxtrx,in,1);
				if (res>0)
				{
					buffer[i] = in[0];
					i++;
				}
			}
		
		log_DEBUG("Message lu : size : %d", size[0]);	
		log_DEBUG("Message lu : (20 first bytes): %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX| ",buffer[0],buffer[1],buffer[2],buffer[3],buffer[4],buffer[5],buffer[6],buffer[7],buffer[8],buffer[9],buffer[10],buffer[11],buffer[12],buffer[13],buffer[14],buffer[15],buffer[16],buffer[17],buffer[18],buffer[19]);	

			
			
		//Check Message received
		if (buffer[0] == size[0])
		{
			log_DEBUG("The message is valid");
	
			switch ( buffer[1] ) {
				case 0x00:
					message_0X00();
					break;
				case 0x01:
					message_0X01(buffer);
					if((buffer[5] != set_mode[5]) || (buffer[7] != set_mode[7]) || (buffer[8] != set_mode[8]) || (buffer[9] != set_mode[9]))
					{
						send_message(set_mode);
						log_DEBUG("Set message sent to RFXTRX433");
					}
					else
					{
						log_DEBUG("RFXTRX433 Correctly set");
					}
					break;
				case 0x02:
					message_0X02();
					break;
				case 0x03:
					message_0X03();
					break;
				case 0x10:
					message_0X10();
					break;
				case 0x11:
					message_0X11(buffer);
					break;
				case 0x14:
					message_0X14(buffer);
					break;
				case 0x1A:
					message_0X1A(buffer);
					break;
				case 0x40:
					message_0X40(buffer);
					break;					
				case 0x52:
					message_0X52(buffer);
					break;
				case 0x55:
					message_0X55(buffer);
					break;
				case 0x56:
					message_0X56(buffer);
					break;
				case 0x5A:
					message_0X5A(buffer);
					break;
				default:
					//Code to execute if <variable> does not equal the value following any of the cases
					log_DEBUG("Type Message non supporte");
					break;
			}
		}
		else
		{
			log_DEBUG("Message non Valide : Buffer[0]: %d, size: %d", buffer[0],size[0]);	
			log_DEBUG("Message non Valide (20 first bytes): %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX| ",buffer[0],buffer[1],buffer[2],buffer[3],buffer[4],buffer[5],buffer[6],buffer[7],buffer[8],buffer[9],buffer[10],buffer[11],buffer[12],buffer[13],buffer[14],buffer[15],buffer[16],buffer[17],buffer[18],buffer[19]);	
		}	
	}
	else
	{
	
	}
	return 0;
}



int send_message(unsigned char *message)
{
	write(fdrfxtrx,message,message[0] + 1);
	log_DEBUG("Message sent: %02hhX", message);
	tcflush(fdrfxtrx, TCIFLUSH);
	return 0;
}



/*
   Write raw bytes to the serial port device
*/

void* rfxtrx433(){
    log_INFO("Starting Rfxtrx433 Module");
    //printf(" openning \n");
    serial_port_open();
		log_DEBUG("Rfxtrx Port Open");
	tcflush(fdrfxtrx, TCIOFLUSH);
		log_DEBUG("Rfxtrx Port IO flush");
		
    send_message(rfx_reset);
		log_DEBUG("Rfxtrx Reset Message Sent");
	sleep (1);
		log_DEBUG("Sleeping 1 sec");
	tcflush(fdrfxtrx, TCIOFLUSH);
		log_DEBUG("Rfxtrx Port IO flush");
    send_message(rfx_status);
		log_DEBUG("Rfxtrx Get Status Sent");	
    send_message(set_mode);
		log_DEBUG("Rfxtrx Mode Message Sent");
		
	while (1){	
		read_rfxtrx();
		tcflush(fdrfxtrx, TCIOFLUSH); 
	}
    return NULL;
}
