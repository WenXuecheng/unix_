#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h> 
#include <sys/stat.h>
#include <net/if.h>
#include <fcntl.h>
#include <stdlib.h>

#define SERVER_PORT 8000
#define MAXLINE 4096

#define CLIENT_PORT 9000
#define GROUP "239.0.0.2"
int main(int argc, char *argv[])
{
        printf("client_udp\n");
        struct sockaddr_in serveraddr, localaddr;
        int confd, len;
        char buf[MAXLINE];
        struct ip_mreqn group;
        //1. socket
        confd = socket(AF_INET, SOCK_DGRAM, 0);
        //2. init add
        bzero(&localaddr, sizeof(localaddr));
        localaddr.sin_family = AF_INET;
        // set add
        inet_pton(AF_INET, "0.0.0.0", &localaddr.sin_addr.s_addr);
        localaddr.sin_port = htons(CLIENT_PORT);
        bind(confd, (struct sockaddr *)&localaddr, sizeof(localaddr));

        
        inet_pton(AF_INET, GROUP, &group.imr_multiaddr);
        inet_pton(AF_INET, "0.0.0.0", &group.imr_address);
//        group.imr_ifindex = if_nametoindex("eth0");
        group.imr_ifindex = 0;

        setsockopt(confd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &group, sizeof(group));

        //3. process data 
        while(1)
        {
                len = recvfrom(confd,buf,sizeof(buf),0,NULL,0);
                write(STDOUT_FILENO,buf,len);
        }
        //4. close
        close(confd);
        return 0;
}
