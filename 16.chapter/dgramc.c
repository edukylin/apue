#include "../apue.h" 
#include <sys/socket.h> 
#include <netinet/in.h> // for INADDR_ANY
#include <arpa/inet.h>  // for inet_ntop
#include <errno.h> 

#define USE_RECVMSG
//#define NO_ADDR

void dump_addr (int fd)
{
    struct sockaddr_in addr = { 0 }; 
    socklen_t len = sizeof (addr); 
    int ret = getsockname (fd, (struct sockaddr *)&addr, &len); 
    if (ret == -1) {
        printf ("getsockname failed, errno %d\n", errno); 
        return; 
    }

    char buf[INET_ADDRSTRLEN] = { 0 }; 
    char const *ptr = inet_ntop (AF_INET, &addr.sin_addr, buf, INET_ADDRSTRLEN); 
    printf ("local addr %d: %s\n", len, ptr ? ptr : "unknown"); 

    len = sizeof (addr); 
    ret = getpeername (fd, (struct sockaddr *)&addr, &len); 
    if (ret == -1) {
        printf ("getpeername failed, errno %d\n", errno); 
        return; 
    }

    ptr = inet_ntop (AF_INET, &addr.sin_addr, buf, INET_ADDRSTRLEN); 
    printf ("remote addr %d: %s\n", len, ptr ? ptr : "unknown"); 

}

int main (int argc, char *argv[])
{
    if (argc < 2)
    {
        printf ("Usage: dgramc port\n"); 
        return -1; 
    }

    unsigned short port = atoi (argv[1]); 
    int fd = -1; 

    do
    {
        fd = socket (AF_INET, SOCK_DGRAM, 0); 
        if (fd == -1) {
            printf ("socket call failed, errno %d\n", errno); 
            break; 
        }

        int ret = 0; 
        struct sockaddr_in addr = { 0 }; 
        addr.sin_addr.s_addr = INADDR_ANY; 
        addr.sin_port = htons (port); 

        int n = 0; 
        char dbuf[128] = { 0 }; 
        char buf[INET_ADDRSTRLEN] = { 0 }; 
        char *ptr = NULL; 
        socklen_t len = 0; 
        while (1)
        {
            sprintf (dbuf, "this is %d", n++); 
            ret = sendto (fd, dbuf, strlen (dbuf), 0, (struct sockaddr *)&addr, sizeof (addr)); 
            if (ret == -1) { 
                printf ("sendto call failed, errno %d\n", errno); 
                break; 
            }

            printf ("client sendto %d\n", ret); 
            if (ret == 0) {
                printf ("no more data, quit..\n"); 
                break; 
            }

            dump_addr (fd); 
            len = sizeof (addr); 
#ifdef USE_RECVMSG
            int i = 0; 
            ptr = dbuf; 
            const int IOVSIZE = 4; 
            struct iovec iv[IOVSIZE]; 
            for (i=0; i<IOVSIZE; ++ i)
            {
                iv[i].iov_base = ptr; 
                iv[i].iov_len = sizeof (dbuf) / IOVSIZE - 1;
                ptr[0] = 0; 
                ptr += iv[i].iov_len + 1; 
            }

            struct msghdr mh = { 0 }; 
            mh.msg_name = &addr; 
            mh.msg_namelen = len; 
            mh.msg_iov = iv; 
            mh.msg_iovlen = IOVSIZE;
            mh.msg_control = 0; 
            mh.msg_controllen = 0; 
            mh.msg_flags = 0; 
            ret = recvmsg (fd, &mh, 0); 
#else
#  ifdef NO_ADDR
            ret = recvfrom (fd, dbuf, sizeof (dbuf), 0, 0, 0); 
#  else
            ret = recvfrom (fd, dbuf, sizeof (dbuf), 0, (struct sockaddr *)&addr, &len); 
            if (ret > 0)
            {
                printf ("recv from %s:%d\n", inet_ntoa(addr.sin_addr), ntohs(addr.sin_port)); 
            }
#  endif
#endif
            if (ret == -1) { 
                printf ("recvfrom/msg call failed, errno %d\n", errno); 
                break; 
            }

            printf ("client recvfrom %d\n", ret); 
            // do patch for all kind..
            for (i=0; i<ret; ++ i)
            {
                // make multi-str to single str
                if (dbuf[i] == 0)
                    dbuf[i] = ' '; 
            }

#ifdef USE_RECVMSG
            printf ("addr: %s:%d, flags: %d\n", inet_ntoa(addr.sin_addr), ntohs(addr.sin_port), mh.msg_flags); 
            for (i=0; i<IOVSIZE; ++ i)
            {
                ((char *)iv[i].iov_base)[iv[i].iov_len] = 0; 
                printf ("%d [%d]: %s\n", i, iv[i].iov_len, iv[i].iov_base); 
            }
#else
            dbuf[ret] = 0; 
            printf ("   %s\n", dbuf); 
#endif 
            sleep (10); 
        }
    } while (0); 

    if (fd != -1)
        close (fd); 

    return 0; 
}
