#include <stdio.h>   /* Standard input/output definitions */
#include <stdlib.h>
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */

#define BAUDRATE B57600
#define PORT_EOUSB300 "/dev/ttyUSB0"
//#define PORT_EOUSB300 "/dev/tty.usbserial-FTXGRVK8"
#define POSIX_SOURCE 1 /* POSIX compliant source */



int fdeousb300;
struct termios oldconfig,newconfig;

char u8CRC8Table[256] = {
    0x00, 0x07, 0x0e, 0x09, 0x1c, 0x1b, 0x12, 0x15,
    0x38, 0x3f, 0x36, 0x31, 0x24, 0x23, 0x2a, 0x2d,
    0x70, 0x77, 0x7e, 0x79, 0x6c, 0x6b, 0x62, 0x65,
    0x48, 0x4f, 0x46, 0x41, 0x54, 0x53, 0x5a, 0x5d,
    0xe0, 0xe7, 0xee, 0xe9, 0xfc, 0xfb, 0xf2, 0xf5,
    0xd8, 0xdf, 0xd6, 0xd1, 0xc4, 0xc3, 0xca, 0xcd,
    0x90, 0x97, 0x9e, 0x99, 0x8c, 0x8b, 0x82, 0x85,
    0xa8, 0xaf, 0xa6, 0xa1, 0xb4, 0xb3, 0xba, 0xbd,
    0xc7, 0xc0, 0xc9, 0xce, 0xdb, 0xdc, 0xd5, 0xd2,
    0xff, 0xf8, 0xf1, 0xf6, 0xe3, 0xe4, 0xed, 0xea,
    0xb7, 0xb0, 0xb9, 0xbe, 0xab, 0xac, 0xa5, 0xa2,
    0x8f, 0x88, 0x81, 0x86, 0x93, 0x94, 0x9d, 0x9a,
    0x27, 0x20, 0x29, 0x2e, 0x3b, 0x3c, 0x35, 0x32,
    0x1f, 0x18, 0x11, 0x16, 0x03, 0x04, 0x0d, 0x0a,
    0x57, 0x50, 0x59, 0x5e, 0x4b, 0x4c, 0x45, 0x42,
    0x6f, 0x68, 0x61, 0x66, 0x73, 0x74, 0x7d, 0x7a,
    0x89, 0x8e, 0x87, 0x80, 0x95, 0x92, 0x9b, 0x9c,
    0xb1, 0xb6, 0xbf, 0xb8, 0xad, 0xaa, 0xa3, 0xa4,
    0xf9, 0xfe, 0xf7, 0xf0, 0xe5, 0xe2, 0xeb, 0xec,
    0xc1, 0xc6, 0xcf, 0xc8, 0xdd, 0xda, 0xd3, 0xd4,
    0x69, 0x6e, 0x67, 0x60, 0x75, 0x72, 0x7b, 0x7c,
    0x51, 0x56, 0x5f, 0x58, 0x4d, 0x4a, 0x43, 0x44,
    0x19, 0x1e, 0x17, 0x10, 0x05, 0x02, 0x0b, 0x0c,
    0x21, 0x26, 0x2f, 0x28, 0x3d, 0x3a, 0x33, 0x34,
    0x4e, 0x49, 0x40, 0x47, 0x52, 0x55, 0x5c, 0x5b,
    0x76, 0x71, 0x78, 0x7f, 0x6A, 0x6d, 0x64, 0x63,
    0x3e, 0x39, 0x30, 0x37, 0x22, 0x25, 0x2c, 0x2b,
    0x06, 0x01, 0x08, 0x0f, 0x1a, 0x1d, 0x14, 0x13,
    0xae, 0xa9, 0xa0, 0xa7, 0xb2, 0xb5, 0xbc, 0xbb,
    0x96, 0x91, 0x98, 0x9f, 0x8a, 0x8D, 0x84, 0x83,
    0xde, 0xd9, 0xd0, 0xd7, 0xc2, 0xc5, 0xcc, 0xcb,
    0xe6, 0xe1, 0xe8, 0xef, 0xfa, 0xfd, 0xf4, 0xf3
};
#define proccrc8(u8CRC, u8Data) (u8CRC8Table[u8CRC ^ u8Data])

/*
* 'open_port()' - Open serial port 1.
*
* Returns the file descriptor on success or -1 on error.
*/
int serial_port_open(void)
{
	printf("Starting Listening on %s \n", PORT_EOUSB300);
	
	fdeousb300 = open(PORT_EOUSB300, O_RDWR | O_NONBLOCK ); 

	if (fdeousb300 == -1)
	{
	/*
	* Could not open the port.
	*/
		perror("open_port: Unable to open Serial Port \n");
		printf("open_port: Unable to open Serial Port \n");
		exit(1);

	}	

	//RECONFIGURATION
	/* get the current options */
    tcgetattr(fdeousb300, &oldconfig); /* save current port settings */
	bzero(&newconfig, sizeof(newconfig));
    
	newconfig.c_cc[VMIN]  = 1;
    newconfig.c_cc[VTIME] = 0;
	
	/* Enable the receiver and set local mode */
	newconfig.c_cflag   = ( CREAD | CLOCAL );
    

    // set to 8N1
    newconfig.c_cflag &= ~PARENB; // no parentybyte
    newconfig.c_cflag &= ~CSTOPB; // 1 stop bit
    newconfig.c_cflag &= ~CSIZE; // Mask the character size bits
    newconfig.c_cflag |= CS8; // 8 data bits
    
    //vitesse du port
	cfsetispeed(&newconfig, BAUDRATE);
    cfsetospeed(&newconfig, BAUDRATE);
        
	/* clear buffer serial*/
	tcflush(fdeousb300, TCIFLUSH);

	/* set the options */
	tcsetattr(fdeousb300,TCSANOW,&newconfig);
	//FIN RECONFIGURATION
	
return (fdeousb300);
}

void read_enocean()
{

	int i;
	char buf[256] = "";
	char sync[1] = "";

	// Loop Waiting for sync Byte 0x55
	while ( sync[0] != 0x55)
	{
        read(fdeousb300,sync,1);   	/* returns after 255 chars have been input */
	}
	
    printf("----------------------\n");
	printf("Byte 0x55 Sync Detected \n");
    
    int red = read(fdeousb300,buf,255);	// Read message without sync charactere
    
    printf("nombre octect lu : %d \n" , red);

    //CRC HEADER Calculation;
    int u8CRC = 0;
    for (i = 0 ; i < 4 ; i++)
    {
        u8CRC = proccrc8(u8CRC, buf[i]);
    }

    printf("Message Received: %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX\n", buf[0],buf[1],buf[2],buf[3],buf[4],buf[5],buf[6],buf[7],buf[8],buf[9],buf[10],buf[11],buf[12],buf[13],buf[14],buf[15],buf[16],buf[17],buf[18],buf[19],buf[20],buf[21],buf[22],buf[23],buf[24],buf[25],buf[26],buf[27],buf[28],buf[29]);
    
	
	if (u8CRC == buf[4]) // If HEADER CRC ok Caluculate message CRC
	{
		printf("HEADER CRC OK, Checking DATA CRC ...\n");
       
        //CRC DATA position calculation
        int crcdata = (((buf[0] << 8) | (buf[1])) + buf[2] + 5);
        
        //CRC DATA Calculation;
        u8CRC = 0;
        for (i=5;i<crcdata;i++)
        {
            u8CRC = proccrc8(u8CRC, buf[i]);
        }
        
        printf("CRC DATA calculated = %02X\n", u8CRC);
        
        if ( u8CRC == buf[crcdata] )
        {
            printf("Message valid, CRC DATA OK \n");
            
            switch ( buf[3] ) {
                case 0x00:
                    printf("PacketType : Reserved \n");
                    break;
                case 0x01:
                    printf("PacketType : RADIO Radio telegram \n");
                    break;
                case 0x02:
                    printf("RESPONSE Response to any packet \n");
                    break;
                case 0x03:
                    printf("RADIO_SUB_TEL Radio subtelegram \n");
                    break;
                case 0x04:
                    printf("EVENT Event message \n");
                    break;
                case 0x05:
                    printf("COMMON_COMMAND Common command \n");
                    break;
                case 0x06:
                    printf("SMART_ACK_COMMAND Smart Ack command \n");
                    break;
                case 0x07:
                    printf("REMOTE_MAN_COMMAND Remote management command \n");
                    break;
                default:
                    //Code to execute if <variable> does not equal the value following any of the cases
                    printf("PacketType  non supporte");
                    break;
            }
      
        }
        else
        {
            printf("Message Wrong, CRC DATA KO \n");
            
        }
        
	}
    else
    {
		printf("----------------------\n");
		printf("Message Wrong, CRC HEADER KO \n");
	
    }
}


void* main(){

    	printf("Starting EnOcean USB300 Module \n");
    	//printf(" openning \n");
    	serial_port_open();
	printf("EnOcean USB300 Port Open \n");
		
	while(1){	
		read_enocean();
	}
}
