#ifndef _APUE_H_
#define _APUE_H_

#define _XOPEN_SOURCE 600 /* Single Unix Specification, Version 3 */

#include <sys/types.h> 
#include <sys/stat.h> 
#include <sys/termios.h> 

#ifndef TIOCGWINSZ
#  include <sys/ioctl.h> 
#endif 

#include <stdio.h> 
#include <stdlib.h> 
#include <stddef.h> 
#include <string.h> 
#include <unistd.h> 
#include <signal.h> 
#include <fcntl.h> 

#define MAXLINE 4096

#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
#define DIR_MODE (FILE_MODE | S_IXUSR | S_IXGRP | S_IXOTH) 

typedef void Sigfunc (int); 

#if defined (SIG_IGN) && !defined (SIG_ERR)
#  define SIG_ERR((Sigfunc *) -1)
#endif 

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))


void err_dump (const char *, ...); 
void err_msg (const char *, ...); 
void err_quit (const char *, ...); 
void err_exit (int, const char *, ...); 
void err_ret (const char *, ...); 
void err_sys (const char *, ...); 

void log_msg (const char *, ...); 
void log_open (const char *, int, int); 
void log_quit (const char *, ...); 
void log_ret (const char *, ...); 
void log_sys (const char *, ...); 

char* path_alloc (int *sizep); 
long open_max (void); 


void set_fl (int fd, int flags); 
void clr_fl (int fd, int flags); 

void tell_buf (char const* name, FILE* fp); 
void pr_exit (int status); 

int apue_system (const char *cmdstring);
unsigned int apue_sleep (unsigned int sec); 

void pr_mask (sigset_t *mask); 
void pr_procmask (char const* tip); 
void pr_threadmask (char const* tip); 
void pr_pendmask (char const* tip); 

//typedef void (*Sigfunc) (int signo); 
Sigfunc* apue_signal (int signo, Sigfunc *func); 
void apue_abort (); 

#define SIG2STR_MAX 10
#define APUE_SIG2STR
int sig2str (int signo, char *str);
int str2sig (const char *str, int *signop);

void printids (char const* prompt);
void daemonize (char const* cmd);
int already_running (void);

int lock_reg (int fd, int cmd, int type, off_t offset, int whence, off_t len); 

pid_t lock_test (int fd, int type, off_t *offset, int *whence, off_t *len); 

#define read_lock(fd, offset, whence, len) \
          lock_reg((fd), F_SETLK, F_RDLCK, (offset), (whence), (len))
#define readw_lock(fd, offset, whence, len) \
          lock_reg((fd), F_SETLKW, F_RDLCK, (offset), (whence), (len))
#define write_lock(fd, offset, whence, len) \
          lock_reg((fd), F_SETLK, F_WRLCK, (offset), (whence), (len))
#define writew_lock(fd, offset, whence, len) \
          lock_reg((fd), F_SETLKW, F_WRLCK, (offset), (whence), (len))
#define un_lock(fd, offset, whence, len) \
          lock_reg((fd), F_SETLK, F_UNLCK, (offset), (whence), (len))
#define read_lockable(fd, offset, whence, len) \
          lock_test((fd), F_RDLCK, (offset), (whence), (len))
#define write_lockable(fd, offset, whence, len) \
          lock_test((fd), F_WRLCK, (offset), (whence), (len))

//#define USE_SIGNAL_SYNC
#define USE_PIPE_SYNC
//#define USE_SEM_SYNC
// always fails with this implement, 
// 1. child process can not inherit parent locks
// 2. double lock on same file on same region has no 'block' effective.
//#define USE_FLCK_SYNC 

void SYNC_INIT ();
void SYNC_REINIT ();  // for child only if USE_FLCK_SYNC
void SYNC_TELL (pid_t pid, int child);
void SYNC_WAIT (int child);

ssize_t readn (int fd, void *buf, size_t len); 
ssize_t writen (int fd, void const* buf, size_t len); 

FILE* apue_popen (char const* cmdstr, char const* type); 
int apue_pclose (FILE *fp); 

void print_sockopt (int fd, char const* prompt); 

#endif 
