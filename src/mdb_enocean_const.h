#ifndef MDB_ENOCEAN_CONST_H_INCLUDED
#define MDB_ENOCEAN_CONST_H_INCLUDED

#include <stdbool.h>

#define SYNC_PACKET         0x55
#define HEADER_SIZE	        5

enum ePacketType {
    RESERVED0 = 0,
    RADIO = 1,
    RESPONSE,
    RADIO_SUB_TEL,
    EVENT,
    COMMON_COMMAND,
    SMART_ACK_COMMAND,
    REMOTE_MAN_COMMAND,
    RESERVED_FOR_ENOCEAN,
    RADIO_MESSAGE,
    RADIO_ADVANCED,
};

typedef struct
{
    unsigned short dataLength;
    unsigned char optionalLength;
    unsigned char packetType;
    char crcHeader;

    char* data;
    char crcData;
}sPacket;

typedef struct
{
    int dc_id;
    unsigned char rorg;
    unsigned char func;
    unsigned char type;
    unsigned char id1;
    unsigned char id2;
    unsigned char id3;
    unsigned char id4;
    bool enable;
}EnDevice;

#endif // MDB_ENOCEAN_CONST_H_INCLUDED
