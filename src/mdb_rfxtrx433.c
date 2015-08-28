/* mdb_rfxtrx433.c */

/*
'------------------------------------------------------------------------------------
' Protocol License Agreement
'
' The RFXtrx protocols are owned by RFXCOM, and are protected under applicable
' copyright laws.
'
' ==================================================================================
' = It is only allowed to use this software or any part of it for RFXCOM products. =
' ==================================================================================
'
' The above Protocol License Agreement and the permission notice shall be included
' in all software using the RFXtrx protocols.
'
' Any use in violation of the foregoing restrictions may subject the user to criminal
' sanctions under applicable laws, as well as to civil liability for the breach of the
' terms and conditions of this license.
'------------------------------------------------------------------------------------- 
*/


#include <stdio.h>   /* Standard input/output definitions */
#include <stdlib.h>
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */

#include "mdb_log.h"
#include "mdb_mysql.h"
#include "mdb_decode_rfxcom_messages.h"

#define BAUDRATE B38400
#define MAX_COMMAND_LENGTH 1

extern 	char 	PORT_RFXTRX433[32];

char rfx_reset[14]={0X0D,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00};
char rfx_status[14]={0X0D,0X00,0X00,0X01,0X02,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00};
char set_mode[14]={0X0D,0X00,0X00,0X00,0X03,0X53,0X00,0X40,0X0A,0X2D,0X00,0X00,0X00,0X00};
//char set_mode[14]={0X0D,0X00,0X00,0X00,0X03,0X53,0X00,0X00,0X02,0X00,0X00,0X00,0X00,0X00};


int taille;
int fdrfxtrx; /* File descriptor for the port */
struct termios oldconfig,newconfig;
char read_buffer[256] = {0};


/*
* 'open_port()' - Open serial port 1.
*
* Returns the file descriptor on success or -1 on error.
*/
int serial_port_open(void)
{
	log_INFO("[rfxtrx433] Starting Listening on %s", PORT_RFXTRX433);
	
	fdrfxtrx = open(PORT_RFXTRX433, O_RDWR | O_APPEND | O_NOCTTY | O_SYNC );

	if (fdrfxtrx == -1)
	{
	/*
	* Could not open the port.
	*/
		perror("[rfxtrx433] open_port: Unable to open Serial Port - ");
		log_ERROR("[rfxtrx433] open_port: Unable to open Serial Port");
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
                        log_DEBUG("[rfxtrx433] RFXTRX433 not Correctly set ,Sending config ...");
						send_message(set_mode);
						log_DEBUG("[rfxtrx433] Set message sent to RFXTRX433");
					}
					else
					{
						log_DEBUG("[rfxtrx433] RFXTRX433 Correctly set");
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
	log_DEBUG("Message sent: %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX", message[0],message[1],message[2],message[3],message[4],message[5],message[6],message[7],message[8],message[9],message[10],message[11],message[12],message[13],message[14]);
	tcflush(fdrfxtrx, TCIFLUSH);
	return 0;
}



/*
   Write raw bytes to the serial port device
*/

void* rfxtrx433(){
    log_INFO("[rfxtrx433] Starting Rfxtrx433 Module");
    //printf(" openning \n");
    serial_port_open();
		log_DEBUG("[rfxtrx433] Rfxtrx Port Open");
	tcflush(fdrfxtrx, TCIOFLUSH);
		log_DEBUG("[rfxtrx433] Rfxtrx Port IO flush");

        log_DEBUG("[rfxtrx433] Rfxtrx Reset Message Sent:");
    send_message(rfx_reset);
        log_DEBUG("[rfxtrx433] Sleeping 1 sec");
        sleep (1);
    tcflush(fdrfxtrx, TCIOFLUSH);
		log_DEBUG("[rfxtrx433] Rfxtrx Port IO flush");
		log_DEBUG("[rfxtrx433] Rfxtrx Get Status Sent :");
    send_message(rfx_status);

		
	while (1){	
		read_rfxtrx();
		tcflush(fdrfxtrx, TCIOFLUSH); 
	}
    return NULL;
}
