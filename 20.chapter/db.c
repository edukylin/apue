#include "../apue.h"
#include "apue_db.h"
#include <fcntl.h>
#include <strings.h>
#include <errno.h>

void Usage ()
{
    printf ("Usage: db filename insert key data\n"); 
    printf ("       db filename query key\n"); 
    printf ("       db filename delete key\n"); 
    printf ("       db filename walk\n"); 
    printf ("       db filename dump\n"); 
    exit (-1); 
}

int main (int argc, char *argv[])
{
    if (argc < 3) 
        Usage (); 

    char *filename = argv[1]; 
    char *action = argv[2]; 
    char *key = NULL; 
    char *data = NULL; 
    if (strcasecmp (action, "walk") == 0 
            || strcasecmp (action, "dump") == 0)
    {
        // no extra param
    }
    else if (strcasecmp (action, "delete") == 0 
            || strcasecmp (action, "query") == 0)
    {
        if (argc < 4)
            Usage (); 

        key = argv[3]; 
    }
    else if (strcasecmp (action, "insert") == 0)
    {
        if (argc < 5)
            Usage (); 

        key = argv[3]; 
        data = argv[4]; 
    }
    else 
    {
        Usage (); 
    }

    DBHANDLE db; 
    char *ptr = NULL; 
#ifdef HAS_HASHSIZE
    int hashsize = 0; 
    ptr = getenv ("APUE_DB_HASH_SIZE"); 
    if (ptr)
        hashsize = atoi (ptr); 

    if (hashsize <= 0)
        hashsize = NHASH_DEF; 

    if ((db = db_open (filename, O_RDWR | O_CREAT /*| O_TRUNC*/, FILE_MODE, hashsize)) == NULL)
#else
    if ((db = db_open (filename, O_RDWR | O_CREAT /*| O_TRUNC*/, FILE_MODE)) == NULL)
#endif
        err_sys ("db_open error"); 

    int ret = 0; 
    if (strcasecmp (action, "dump") == 0)
    {
        db_dump (db); 
    }
    else if (strcasecmp (action, "walk") == 0)
    {
        //db_rewind (); 
        int n = 0; 
        char buf[IDXLEN_MAX] = { 0 }; 
        while ((ptr = db_nextrec(db, buf)) != NULL)
        {
            n ++; 
            printf ("[%5d] %s --- %s\n", n, buf, ptr); 
        }

        printf ("walk done!\n"); 
    }
    else if (strcasecmp (action, "insert") == 0)
    {
        ret = db_store (db, key, data, DB_STORE); 
        if (ret < 0)
            fprintf (stderr, "insert %s.%s failed, errno %d\n", key, data, errno); 
        else if (ret == 1)
            fprintf (stderr, "insert %s.%s cover old data\n", key, data); 
        else 
            printf ("db %s '%s' code %d\n", action, key, ret); 
    }
    else if (strcasecmp (action, "delete") == 0)
    {
        ret = db_delete (db, key); 
        if (ret < 0)
            fprintf (stderr, "delete %s failed, errno %d\n", key, errno); 
        else 
            printf ("db %s '%s' code %d\n", action, key, ret); 
    }
    else if (strcasecmp (action, "query") == 0)
    {
        ptr = db_fetch (db, key); 
        //printf ("%s === %s\n", key, ptr); 
        // only print data to allow assigned in shell script
        printf ("%s\n", ptr == NULL ? "nil" : ptr); 
    }
    else
        Usage (); 

    db_close (db); 
    return ret; 
}
