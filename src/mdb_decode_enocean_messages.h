/* mdb_decode_enocean_message.h */
#ifndef __MDB_DECODE_ENOCEAN_MESSAGE_H__
#define __MDB_DECODE_ENOCEAN_MESSAGE_H__

float enDecodeTemperature(int ScaleMin,int ScaleMax,int RangeMin,int RangeMax,int RawData);

EnDevice GetEnDevice(char* data);

bool enMessage_0XD5(char* data);

bool enMessage_0XA5(char* data);

bool decodeEnoceanRadio(char* data);

# endif /* __MDB_DECODE_ENOCEAN_MESSAGE_H__ */