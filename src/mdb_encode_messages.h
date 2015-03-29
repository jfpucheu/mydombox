/* mdb_encode_messages.h */
#ifndef __MDB_ENCODE_MESSAGES_H__
#define __MDB_ENCODE_MESSAGES_H__

int encode_lighting_message(int dc_id, char* state, int dim);

int encode_thermostat_message(int dc_id, float tp_consigne, float tp_current, char* demand);

int encode_init_message(int dc_id, char* order);

# endif /* __MDB_ENCODE_MESSAGES_H__ */
