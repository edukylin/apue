#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <errno.h> 
#include "../../apue.h"

#define MAX_BUFSIZE 512

int main (int argc, char *argv[])
{
    int ret = 0; 
    unsigned short port = 10028; 
    struct sockaddr_in addr; 
    addr.sin_family = AF_INET; 
    addr.sin_port = htons (port); 
    addr.sin_addr.s_addr = htonl (INADDR_ANY); 

    int connfd = socket (PF_INET, SOCK_STREAM, 0); 
    if (connfd < 0)
        err_sys ("create socket"); 

    socklen_t addrlen = sizeof (struct sockaddr_in); 
    ret = connect (connfd, (struct sockaddr *)&addr, addrlen); 
    if (ret < 0)
        err_sys ("connect"); 

    int n = 0, quit = 0; 
    char buf[MAX_BUFSIZE+1] = { 0 }; 
    while (!quit)
    {
      printf (">"); 
      if (fgets (buf, MAX_BUFSIZE, stdin) == NULL)
      {
          printf ("getting user input failed\n"); 
          break; 
      }

      // to skip terminal \n
      if (strncmp (buf, "exit", 4) == 0)
      {
          quit = 1; 
          printf ("%d: %s", quit, buf); 
      }
      

      n = strlen (buf) + 1; 
      ret = send (connfd, buf, n, 0);
      if (ret < n)
      {
          printf ("send failed, %d != %d\n", ret, n); 
          break; 
      }

      usleep (100000); 

      do
      {
        ret = recv (connfd, buf, sizeof(buf), MSG_DONTWAIT); 
        if (ret <= 0)
        {
            if (errno == EAGAIN)
                break; 

            printf ("recv failed, errno %d\n", errno); 
            break; 
        }

        buf[ret] = 0; 
        printf ("%s", buf); 
      }while (1); 
    }
 
    printf ("connection break...\n"); 
    close (connfd); 
    return 0; 
}
