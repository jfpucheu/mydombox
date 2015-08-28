#ifndef MDB_ENOCEAN_USB300_H_INCLUDED
#define MDB_ENOCEAN_USB300_H_INCLUDED

#include <stdbool.h>

#include "mdb_enocean_const.h"

bool checkCrc(char* data, int dataLength, char crc);

bool readData(char* data, int dataLen);

bool readHeader(sPacket* packet);

bool readMessageData(sPacket* packet);

bool openEnoceanDevice(void);

void waitSync();

void readEnocean();

void* enusb300();

#endif
