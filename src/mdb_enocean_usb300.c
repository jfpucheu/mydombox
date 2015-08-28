/* mdb_enocean_usb300.c */

#include <stdio.h>   /* Standard input/output definitions */
#include <stdlib.h>
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */

#include "mdb_log.h"
#include "mdb_enocean_const.h"
#include "mdb_decode_enocean_messages.h"

#define BAUDRATE B57600
#define POSIX_SOURCE 1 /* POSIX compliant source */
#define HEADER_SIZE	5

#define DELETE_SAFE(X) {free(X); X = NULL; }

extern 	char 	PORT_ENOUSB300[32];
int enoceanHandle = -1;
int fdeousb300;
struct termios oldconfig, newconfig;

char crc8Table[256] = {
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

bool checkCrc(char* data, int dataLength, char crc)
{
    int u8Crc = 0;
    int i;
    for(i = 0 ; i < dataLength ; i++)
        u8Crc = crc8Table[u8Crc ^ data[i]];
    return (crc == u8Crc);
}

void waitSync()
{
    char sync;
    
    while(sync != SYNC_PACKET)
    {
        int len = read(enoceanHandle, &sync, 1);
        //if(len <= 0){
        //log_DEBUG("[EnOcean] Time Out Sync : res = %d \r\n", len);
        //}
    }
    
}

bool readData(char* data, int dataLen)
{
    if((data == NULL) || (dataLen < 1)) return false;
    
    int len = 0;
    while(dataLen > 0)
    {
        int size = read(enoceanHandle, data + len, dataLen);
        
        if(size <= 0)
        {
            //log_DEBUG("[EnOcean] Time Out Stream : res = %d \r\n", size);
            return false;
        }
        
        dataLen -= size;
        len += size;
    }
    return true;
}

bool readHeader(sPacket* packet)
{
    if(packet == NULL) return false;
    
    char data[HEADER_SIZE];
    
    if(!readData((char*) data, HEADER_SIZE)) return false;
    
    char crcHeader = data[4];
    
    if(!checkCrc(data, HEADER_SIZE - 1, crcHeader)) return false;
    
    packet->dataLength = (data[0] << 8) | data[1];
    packet->optionalLength = data[2];
    packet->packetType = data[3];
    packet->crcHeader = crcHeader;
    
    return true;
}

bool readMessageData(sPacket* packet)
{
    if(packet == NULL) return false;
    
    int lenAllData = packet->dataLength + packet->optionalLength;
    
    if(packet->data != NULL)
    {
        free(packet->data);
        packet->data = NULL;
    }
    
    packet->data = (char*)malloc(sizeof(char) * lenAllData);
    
    if(!readData(packet->data, lenAllData))
    {
        DELETE_SAFE(packet->data);
        return false;
    }
    if(!readData(&packet->crcData, 1))
    {
        DELETE_SAFE(packet->data);
        return false;
    }
    
    if(!checkCrc(packet->data, lenAllData, packet->crcData))
    {
        DELETE_SAFE(packet->data);
        return false;
    }
    return true;
}

bool getStreamPacket(sPacket* packet)
{
    if(packet == NULL) return false;
    
    DELETE_SAFE(packet->data);
    
    waitSync(); // Loop Waiting for sync Byte 0x55
    if(!readHeader(packet)) return false;
    if(!readMessageData(packet)) return false;
    
    return true;
}

bool openEnoceanDevice(void)
{
    log_INFO("[EnOcean] Starting Listening on %s \n", PORT_ENOUSB300);
    
    enoceanHandle = open(PORT_ENOUSB300, O_RDWR | O_NOCTTY);
    
    if (enoceanHandle == -1)
    {
        // Could not open the port.
        perror("[EnOcean] open_port: Unable to open Serial Port \n");
        log_ERROR("[EnOcean] open_port: Unable to open Serial Port \n");
        exit(1);
    }
    
    // get the current options
    tcgetattr(enoceanHandle, &oldconfig); // save current port settings
    bzero(&newconfig, sizeof(newconfig));
    
    newconfig.c_cc[VMIN]  = 0;
    newconfig.c_cc[VTIME] = 10; // time out 1 second (0.1 * value) ms
    
    // Enable the receiver and set local mode
    newconfig.c_cflag   = ( CREAD | CLOCAL );
    
    // set to 8N1
    newconfig.c_cflag &= ~PARENB; // no parentybyte
    newconfig.c_cflag &= ~CSTOPB; // 1 stop bit
    newconfig.c_cflag &= ~CSIZE; // Mask the character size bits
    newconfig.c_cflag |= CS8; // 8 data bits
    
    //port speed
    cfsetispeed(&newconfig, BAUDRATE);
    cfsetospeed(&newconfig, BAUDRATE);
    
    // clear buffer serial
    tcflush(enoceanHandle, TCIFLUSH);
    
    // set the options
    tcsetattr(enoceanHandle, TCSANOW, &newconfig);
    
    return (enoceanHandle != -1);
}


void readEnocean()
{
    sPacket packet;
    
    packet.data = NULL;
    
    if(getStreamPacket(&packet))
    {
        log_DEBUG("[EnOcean] Message received \r\n");
        
        switch (packet.packetType)
        {
            case RESERVED0:
                log_DEBUG("[EnOcean] PacketType : Reserved \r\n");
                break;
                
            case RADIO:
            {
                int i = 0;
                static char datastring[128];
                static char optionaldatastring[128];
                
                log_DEBUG("[EnOcean] PacketType: RADIO Radio telegram \r");
                
                for(i = 0; i < packet.dataLength; i++)
                {
                    //printf(" %02X", packet.data[i]);
                    sprintf(&datastring[i*3]," %02x", packet.data[i]);
                }
                log_DEBUG("[EnOcean] Data = %s",datastring);
 
                for(i = 0; i < packet.optionalLength; i++)
                {
                    //printf(" %02X", packet.data[packet.dataLength + i]);
                    sprintf(&optionaldatastring[i*3]," %02x", packet.data[packet.dataLength + i]);
                }
                log_DEBUG("[EnOcean] Optional Data = %s",optionaldatastring);
                
                decodeEnoceanRadio(packet.data);

                
            }
                break;
                
            case RESPONSE:
                log_DEBUG("[EnOcean] RESPONSE Response to any packet");
                break;
                
            case RADIO_SUB_TEL:
                log_DEBUG("[EnOcean] RADIO_SUB_TEL Radio subtelegram");
                break;
                
            case EVENT:
                log_DEBUG("[EnOcean] EVENT Event message");
                break;
                
            case COMMON_COMMAND:
                log_DEBUG("[EnOcean] COMMON_COMMAND Common command");
                break;
                
            case SMART_ACK_COMMAND:
                log_DEBUG("[EnOcean] SMART_ACK_COMMAND Smart Ack command");
                break;
                
            case REMOTE_MAN_COMMAND:
                log_DEBUG("[EnOcean] REMOTE_MAN_COMMAND Remote management command");
                break;
                
            default:
                log_DEBUG("[EnOcean] PacketType  non supporte");
                break;
        }
    }
}


void* enusb300()
{
    log_INFO("[EnOcean] Starting EnOcean USB300 Module");
    if(openEnoceanDevice())
    {
        log_INFO("[EnOcean] ENOUSB300 Port Open");
        
        while(true)
        {
            readEnocean();
        }
    }
    return 0;
}

