/* mdb_enocean_usb300.c */

#include <stdio.h>   /* Standard input/output definitions */
#include <stdlib.h>
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */

//#include "mdb_log.h"

#define BAUDRATE B57600
#define MAX_COMMAND_LENGTH 1

char 	PORT_EOUSB300[32]="/dev/ttyUSB0";

char enocean_reset[14]={0X0D,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00};
char enocean_status[14]={0X0D,0X00,0X00,0X01,0X02,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00};
char set_mode[14]={0X0D,0X00,0X00,0X00,0X03,0X53,0X00,0X00,0X0A,0X2D,0X00,0X00,0X00,0X00};
//char set_mode[14]={0X0D,0X00,0X00,0X00,0X03,0X53,0X00,0X00,0X02,0X00,0X00,0X00,0X00,0X00};


int taille;
int fdenocean; /* File descriptor for the port */
struct termios oldconfig,newconfig;
char read_buffer[256] = {0};


/*
* 'open_port()' - Open serial port 1.
*
* Returns the file descriptor on success or -1 on error.
*/
int serial_port_open(void)
{
	printf("Starting Listening on %s", PORT_EOUSB300);
	
	fdenocean = open(PORT_EOUSB300, O_RDWR | O_APPEND | O_NOCTTY | O_SYNC );

	if (fdenocean == -1)
	{
	/*
	* Could not open the port.
	*/
		perror("open_port: Unable to open Serial Port - ");
		printf("open_port: Unable to open Serial Port");
		exit(1);

	}

	//RECONFIGURATION
	/* get the current options */
    tcgetattr(fdenocean, &oldconfig);
	bzero(&newconfig, sizeof(newconfig));
	
	newconfig.c_cc[VMIN]  = 1;
    newconfig.c_cc[VTIME] = 0;
	
	/* Enable the receiver and set local mode */
	newconfig.c_cflag   = ( CS8 | CREAD | CLOCAL );
	
	/* vitesse du port*/
	cfsetispeed(&newconfig, BAUDRATE); 
    cfsetospeed(&newconfig, BAUDRATE);
	
	/* clear buffer serial*/
	tcflush(fdenocean, TCIOFLUSH);
	
    /* set the options */
	tcsetattr(fdenocean, TCSANOW, &newconfig);
	//FIN RECONFIGURATION
	

return (fdenocean);
}	

int read_enocean(void)
{
	int res,i=1;
	char in[1],size[1];
	char buffer[255]={'\0'}; /* Input buffer */
	
	res = read(fdenocean,size,1);

        if (res>0)
        {
			buffer[0]=size[0];
			
			while (i <= size[0])
			{
				res = read(fdenocean,in,1);
				if (res>0)
				{
					buffer[i] = in[0];
					i++;
				}
			}
		
		printf("Message lu : size : %d", size[0]);
		printf("Message lu : (20 first bytes): %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX| ",buffer[0],buffer[1],buffer[2],buffer[3],buffer[4],buffer[5],buffer[6],buffer[7],buffer[8],buffer[9],buffer[10],buffer[11],buffer[12],buffer[13],buffer[14],buffer[15],buffer[16],buffer[17],buffer[18],buffer[19]);

			
			
		//Check Message received
		if (buffer[0] == size[0])
		{
			printf("The message is valid");
	
			switch ( buffer[1] ) {
				case 0x00:
					//message_0X00();
					break;
				case 0x01:
					//message_0X01(buffer);
					if((buffer[5] != set_mode[5]) || (buffer[7] != set_mode[7]) || (buffer[8] != set_mode[8]) || (buffer[9] != set_mode[9]))
					{
                        printf("ENOCEAN USB300 not Correctly set ,Sending config ...");
						//send_enocean(set_mode);
						printf("Set message sent to ENOCEAN USB300 ");
					}
					else
					{
						printf("ENOCEAN USB300  Correctly set");
					}
					break;
				case 0x02:
					//message_0X02();
					break;
				case 0x03:
					//message_0X03();
					break;
				case 0x10:
					//message_0X10();
					break;
				case 0x11:
					//message_0X11(buffer);
					break;
				case 0x14:
					//message_0X14(buffer);
					break;
				case 0x1A:
					//message_0X1A(buffer);
					break;
				case 0x40:
					//message_0X40(buffer);
					break;					
				case 0x52:
					//message_0X52(buffer);
					break;
				case 0x55:
					//message_0X55(buffer);
					break;
				case 0x56:
					//message_0X56(buffer);
					break;
				case 0x5A:
					//message_0X5A(buffer);
					break;
				default:
					//Code to execute if <variable> does not equal the value following any of the cases
					printf("Type Message non supporte");
					break;
			}
		}
		else
		{
			printf("Message non Valide : Buffer[0]: %d, size: %d", buffer[0],size[0]);
			printf("Message non Valide (20 first bytes): %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX| ",buffer[0],buffer[1],buffer[2],buffer[3],buffer[4],buffer[5],buffer[6],buffer[7],buffer[8],buffer[9],buffer[10],buffer[11],buffer[12],buffer[13],buffer[14],buffer[15],buffer[16],buffer[17],buffer[18],buffer[19]);
		}	
	}
	else
	{
	
	}
	return 0;
}



int send_enocean(unsigned char *message)
{
	write(fdenocean,message,message[0] + 1);
	printf("Message sent: %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX", message[0],message[1],message[2],message[3],message[4],message[5],message[6],message[7],message[8],message[9],message[10],message[11],message[12],message[13],message[14]);
	tcflush(fdenocean, TCIFLUSH);
	return 0;
}



/*
   Write raw bytes to the serial port device
*/

int main(){
    printf("Starting Enocean USB300 Module\n");
    printf(" openning \n");
    serial_port_open();
		printf("Enocean USB300 Port Open\n");
	//tcflush(fdenocean, TCIOFLUSH);
		printf("Enocean USB300 Port IO flush\n");

        printf("Enocean USB300 Reset Message Sent:\n");
    //send_enocean(rfx_reset);
        printf("Sleeping 1 sec");
        sleep (1);
    //tcflush(fdenocean, TCIOFLUSH);
		printf("Enocean USB300 Port IO flush\n");
		printf("Enocean USB300 Get Status Sent :\n");
    //send_enocean(rfx_status);

		
	while (1){
		read_enocean();
		tcflush(fdenocean, TCIOFLUSH);
	}
//    return NULL;
}
