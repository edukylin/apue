#include "../apue.h" 
#include <fcntl.h> 
#include <strings.h> 
#include <errno.h> 
#include <limits.h>

//#define USE_DUP
#define USE_REOPEN

void usage ()
{
    printf (
      "Usage:\n"
      "action: LOCK/LOCKWAIT/UNLOCK/TESTLOCK\n"
      "type: READ/WRITE\n"
      "whence: SET/CUR/END\n"
      "mode: CLOSE/DUP/REOPEN\n"
      "filelock path action type offset whence len mode\n"
      ); 
    exit (-1); 
}

void dump_lock (char const* act, struct flock *lck)
{
  printf ("[%lu] %s %s (%d, %d) @ %s\n", 
      getpid (), 
      act, 
      lck->l_type == F_RDLCK 
        ? "rdlock" 
        : (lck->l_type == F_WRLCK 
          ? "wrlock" 
          : "unlock"), 
      lck->l_len > 0 
        ? lck->l_start 
        : lck->l_start + lck->l_len, 
      lck->l_len > 0 
        ? lck->l_start + lck->l_len 
        : lck->l_len == 0 
          ? INT_MAX 
          : lck->l_start, 
      lck->l_whence == SEEK_SET 
        ? "beg" 
        : (lck->l_whence == SEEK_CUR 
          ? "cur" 
          : "end")); 
}

int main (int argc, char *argv[])
{
  if (argc != 8)
    usage (); 

  off_t offset = atoi(argv[4]); 
  off_t len = atoi(argv[6]); 
  int whence = 0; 
  if (strcasecmp (argv[5], "SET") == 0)
    whence = SEEK_SET; 
  else if (strcasecmp (argv[5], "CUR") == 0)
    whence = SEEK_CUR; 
  else if (strcasecmp (argv[5], "END") == 0)
    whence = SEEK_END; 
  else
    usage (); 

  int type = 0; 
  if (strcasecmp (argv[3], "READ") == 0)
    type = F_RDLCK; 
  else if (strcasecmp (argv[3], "WRITE") == 0)
    type = F_WRLCK; 
  else 
    usage (); 

  int mode = 0; 
  if (strcasecmp (argv[7], "CLOSE") == 0)
    mode = 0; 
  else if (strcasecmp (argv[7], "DUP") == 0)
    mode = 1; 
  else if (strcasecmp (argv[7], "REOPEN") == 0)
    mode = 2; 
  else 
    usage (); 

  int fd = open (argv[1], type == F_RDLCK ? O_RDONLY : O_WRONLY); 
  if (fd == -1)
    err_sys ("open %s failed", argv[1]); 

  int action = 0; 
  if (strcasecmp (argv[2], "LOCK") == 0)
    action = F_SETLK; 
  else if (strcasecmp (argv[2], "LOCKWAIT") == 0)
    action = F_SETLKW; 
  else if (strcasecmp (argv[2], "UNLOCK") == 0)
  {
    action = F_SETLK; 
    type = F_UNLCK; 
  }
  else if (strcasecmp (argv[2], "TESTLOCK") == 0)
    action = F_GETLK; 
  else 
    usage (); 

  //printf ("%lu start\n", getpid ()); 
  struct flock lock; 
  lock.l_type = type; 
  lock.l_start = offset; 
  lock.l_whence = whence; 
  lock.l_len = len; 
  dump_lock (argv[2], &lock); 
  int ret = fcntl (fd, action, &lock); 
  if (ret == -1)
    err_sys ("fcntl failed, errno %d", errno); 

  if (action == F_GETLK)
  {
    // dump result
    if (lock.l_type == F_UNLCK)
      printf ("no lock in destination found\n"); 
    else 
    {
      printf ("find a lock owning by %lu\n", lock.l_pid); 
      dump_lock ("FINDLOCK", &lock); 
    }
  }
  else 
  {
    printf ("[%lu] got lock\n", getpid ()); 
    sleep (2); 

    if (mode == 0) {
      close (fd); 
      printf ("[%lu] close handler %d\n", getpid (), fd); 
    } 
    else if (mode == 1) { 
      int fd2 = dup (fd); 
      close (fd2); 
      printf ("[%lu] dup handler %d (from %d) and closed\n", getpid (), fd2, fd); 
    } 
    else if (mode == 2) { 
      int fd2= open (argv[1], type == F_RDLCK ? O_RDONLY : O_WRONLY); 
      if (fd2== -1)
        err_sys ("reopen %s failed", argv[1]); 
      else {
        close (fd2); 
        printf ("[%lu] reopen handler %d (original %d) and closed\n", getpid (), fd2, fd); 
      }
    }
    sleep (8); 
  }

  printf ("%lu exit\n", getpid ()); 
}
