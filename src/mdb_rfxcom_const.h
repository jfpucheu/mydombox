#ifndef MDB_RFXCOM_CONST_H_INCLUDED
#define MDB_RFXCOM_CONST_H_INCLUDED

#include <stdbool.h>

typedef struct
{
    int dc_id;
    unsigned char packettype;
    unsigned char subtype;
    unsigned char id1;
    unsigned char id2;
    unsigned char id3;
    unsigned char id4;
    unsigned char unitcode;
    bool enable;
}RfxDevice;

#endif // MDB_RFXCOM_CONST_H_INCLUDED
