#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <ctype.h>
#define CLIENT_PORT 9000
#define SERVER_PORT 8000
#define MAXLINE 1500
#define GROUP "239.0.0.2"
int main(void)
{
        printf("server_udp\n");
        int sockfd, i;
        ssize_t len;
        struct sockaddr_in serveraddr, clientaddr;
        char buf[MAXLINE] = "hello!\n", ipstr[INET_ADDRSTRLEN];
        socklen_t clientlen;
        struct ip_mreqn group;

        sockfd = socket(AF_INET, SOCK_DGRAM, 0);

        bzero(&serveraddr, sizeof(serveraddr));
        serveraddr.sin_family = AF_INET;
        serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
        serveraddr.sin_port = htons(SERVER_PORT);

        bind(sockfd, (struct sockaddr *) &serveraddr, sizeof(serveraddr));
        
        inet_pton(AF_INET, GROUP, &group.imr_multiaddr);
        inet_pton(AF_INET, "0.0.0.0", &group.imr_address);
        //group.imr_ifindex = if_nametoindex("eth0");
        group.imr_ifindex = 0;

        setsockopt(sockfd, IPPROTO_IP, IP_MULTICAST_IF, &group, sizeof(group));

        bzero(&clientaddr, sizeof(clientaddr));
        clientaddr.sin_family = AF_INET;
        inet_pton(AF_INET, GROUP, &clientaddr.sin_addr.s_addr);
        clientaddr.sin_port = htons(CLIENT_PORT);
        while(1)
        {
                //fgets(buf, sizeof(buf), stdin);
                sendto(sockfd, buf, strlen(buf), 0,(struct sockaddr *)&clientaddr, sizeof(clientaddr));
                sleep(1);
        }
        close(sockfd);

        return 0;
}

