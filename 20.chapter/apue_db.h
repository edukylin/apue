#ifndef __APUE_DB_H__
#define __APUE_DB_H__

typedef void* DBHANDLE;

// db_store flags
#define DB_INSERT 1
#define DB_REPLACE 2
#define DB_STORE 3

#define IDXLEN_MIN 6
#define IDXLEN_MAX 1024 // single index can not exceed this size
#define DATLEN_MIN 2
#define DATLEN_MAX 1024 // single data can not exceed this size
#define NHASH_DEF 137 // default hash table size

DBHANDLE db_open (char const* pathname, int oflag, .../*mode*/); 
void db_close (DBHANDLE db); 
int db_store (DBHANDLE db, const char *key, const char *data, int flag); 
char* db_fetch (DBHANDLE db, char *key); 
int db_delete (DBHANDLE db, const char *key); 
void db_rewind (DBHANDLE db); 
char *db_nextrec (DBHANDLE db, char *key); 
void db_dump (DBHANDLE db); 

#endif
