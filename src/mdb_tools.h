/* mdb_tools.h */
#ifndef __MDB_TOOLS_H__
#define __MDB_TOOLS_H__

int whichday();

unsigned char stringtohex(char *hexstr);

unsigned char inttohex(int val);

void print_message(unsigned char *message);

float decode_temperature( char *temperaturehigh, char *temperaturelow);

struct device device_by_id(unsigned char id1,unsigned char id2,unsigned char id3,unsigned char id4, unsigned char unitcode, unsigned char groupcode, unsigned char housecode);

# endif /* __MDB_TOOLS_H__ */