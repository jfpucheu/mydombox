#ifndef MDB_MYDOMBOX_H_INCLUDED
#define MDB_MYDOMBOX_H_INCLUDED

#include <stdbool.h>

typedef struct
{
    int dc_id;
    char* packettype;
    char* subtype
    unsigned char int_id;
    char* address;
    unsigned char id1;
    unsigned char id2;
    unsigned char id3;
    unsigned char id4;
    unsigned char unitcode;
    unsigned char groupcode;
    unsigned char housecode;
    bool enable;
}sDevice;

#endif // MDB_MYDOMBOX_H_INCLUDED
