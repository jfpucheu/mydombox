/* mdb_decode_rfxcom_messages.h */
#ifndef __MDB_DECODE_RFXCOM_MESSAGES_H__
#define __MDB_DECODE_RFXCOM_MESSAGES_H__

#include "mdb_rfxcom_const.h"

void print_device_rfx(RfxDevice variable);

RfxDevice GetRfxDevice(char* data);

bool addRfxDevice(char* data);

void message_0X00();
 
void message_0X01(char message[255]);
 
void message_0X02();

void message_0X03();

void message_0X10();

void message_0X11(char message[255]);

void message_0X14(char message[255]);

void message_0X1A(char message[255]);

void message_0X40(char message[255]);

void message_0X52(char message[255]);

void message_0X55(char message[255]);

void message_0X56(char message[255]);

void message_0X5A(char message[255]);

void message_EDF1(char message[20][18]);

void message_EDF3(char message[20][18]);

void message_1W28(char adresse[16],char message[256]);

# endif /* __MDB_DECODE_RFXCOM_MESSAGES_H__ */
