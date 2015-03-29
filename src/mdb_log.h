/* mdb_log.h */
#ifndef __MDB_LOG_H__
#define __MDB_LOG_H__

void log_DEBUG_SQL(const char * message, ... );

void log_DEBUG(const char * message, ... );

void log_ERROR(const char * message, ... );

void log_INFO(const char * message, ... );

# endif /* __MDB_LOG_H__ */