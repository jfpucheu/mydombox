/* mdb_mysql.h */

#include <mysql.h> 	/* Mysql lib */

#ifndef __MDB_MYSQL_H__
#define __MDB_MYSQL_H__

MYSQL* mysql_connection(void);

int mysql_insert(const char * query, ...);

MYSQL_RES* mysql_select(MYSQL* conn,const char * query, ...);

void mysql_printf_select(const char * query, ...);


# endif /* __MDB_MYSQL_H__ */
