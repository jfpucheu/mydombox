/* mdb_structures.h */
#ifndef __MDB_STRUCTURES_H__
#define __MDB_STRUCTURES_H__

struct device {

	int dc_id;
	char dc_name[25];
	int enable;
	int m2x_status;
	char m2x_name[25];
};

# endif /* __MDB_STRUCTURES_H__ */
