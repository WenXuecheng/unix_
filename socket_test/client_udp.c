#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h> 
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#define SERVER_PORT 8000
#define MAXLINE 4096

int main(int argc, char *argv[])
{
        printf("client_udp\n");
        if (argc < 2)
        {
                printf("too few \n");
                exit(1);
        }
        struct sockaddr_in serveraddr;
        int confd, len;
        char buf[MAXLINE],ipstr[] = "192.168.1.102";
        //1. socket
        confd = socket(AF_INET, SOCK_DGRAM, 0);
        //2. init add
        bzero(&serveraddr, sizeof(serveraddr));
        serveraddr.sin_family = AF_INET;
        // set add
        inet_pton(AF_INET, ipstr, &serveraddr.sin_addr.s_addr);
        serveraddr.sin_port = htons(SERVER_PORT);

        //3. process data 
        sendto(confd,argv[1], strlen(argv[1]), 0, (struct sockaddr *) &serveraddr, sizeof(serveraddr));
        len = recvfrom(confd,buf,sizeof(buf),0,NULL,0);
        write(STDOUT_FILENO,buf,len);
        //4. close
        close(confd);
        return 0;
}
