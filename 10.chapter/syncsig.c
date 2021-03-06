#include "../apue.h" 
#include <sys/wait.h>
#include <errno.h>

#define USE_FSTREAM 2
int read_increase_write ()
{
    char *ptr = NULL; 
    int n = 0, ret = 0, err = 0; 
#ifdef USE_FSTREAM
    FILE* fp = fopen ("sync.txt", "r+"); 
    if (fp)
#else
    int fd = open ("sync.txt", O_CREAT | O_RDWR, 0622); 
    if (fd != -1)
#endif
    {
        char buf[64] = { 0 }; 
        do
        {
            errno = 0; 
#if USE_FSTREAM==1
            ret = fread (buf, 1, sizeof(buf), fp); 
            err = errno; 
            //printf ("read %d, errno %d\n", ret, err); 
        } while (ret == -1 && err == EINTR); 
#elif USE_FSTREAM==2
            ptr = fgets (buf, sizeof(buf), fp); 
            err = errno; 
            //printf ("read %s, errno %d\n", ptr, err); 
        } while (ptr == NULL && err == EINTR); 
#else 
            ret = read (fd, buf, sizeof(buf)); 
            err = errno; 
            //printf ("read %d, errno %d\n", ret, err); 
        } while (ret == -1 && err == EINTR); 
#endif

        n = atoi (buf); 
        memset (buf, 0, sizeof(buf)); 
        sprintf (buf, "%d", ++n); 
        
#ifdef USE_FSTREAM
        fp = freopen ("sync.txt", "w", fp); 
        if (!fp)
            err_sys ("freopen"); 
#endif
        
        do 
        {
            errno = 0; 
#if USE_FSTREAM==1
            //if (fseek (fp, 0, SEEK_SET) == -1)
            //    err_sys ("fseek"); 
            ret = fwrite (buf, strlen(buf)+1, 1, fp); 
#elif USE_FSTREAM==2
            ret = fputs (buf, fp); 
#else 
            if (lseek (fd, 0, SEEK_SET) == -1)
                err_sys ("lseek"); 

            ret = write (fd, buf, strlen(buf)+1); 
#endif
            err = errno; 
            //printf ("write %d, errno %d\n", ret, err); 
        } while (ret == -1 && err == EINTR); 

        printf ("[%d] read %d, write %d\n", getpid (), n-1, n); 
    }
    else 
    {
        printf ("open file failed, errno %d\n", errno); 
        return -1; 
    }

#ifdef USE_FSTREAM
    fclose (fp); 
#else
    close (fd); 
#endif
    return n; 
}

int main (void)
{
    int ret = 0; 
    pid_t cid = 0; 
    //if (apue_signal (SIGUSR1, SIG_IGN) == SIG_ERR)
    //    err_sys ("signal (SIGUSR1) error"); 
    //if (apue_signal (SIGUSR2, SIG_IGN) == SIG_ERR)
    //    err_sys ("signal (SIGUSR2) error"); 

    SYNC_INIT (); 
    cid = fork (); 
    if (cid < 0)
    {
        err_sys ("fork error"); 
        return -1; 
    }
    else if (cid == 0)
    {
        printf ("child %u running\n", getpid ()); 
        //sleep (5); 
        while (ret < 10)
        {
            ret = read_increase_write (); 
            SYNC_TELL (getppid (), 0); 
            printf ("notify parent\n"); 
            if (ret < 0 || ret >= 10)
                break; 

            SYNC_WAIT (1); 
            printf ("wait parent %u\n", getppid ()); 
        }
        return 2; 
    }

    while (ret < 10 && ret >= 0)
    {
        //printf ("prepare to wait child\n"); 
        SYNC_WAIT(0); 
        printf ("wait child\n"); 
        ret = read_increase_write (); 
        SYNC_TELL (cid, 1); 
        printf ("notify child\n"); 
    }

    pid_t wid = 0; 
    int status = 0; 
    //waitpid (cid, &status, 0); 
    if ((wid = wait (&status)) < 0)
        err_sys ("wait error"); 

    printf ("wait child %u exit %d\n", wid, WEXITSTATUS(status)); 
    return 1; 

}
