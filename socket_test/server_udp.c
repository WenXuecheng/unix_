#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <ctype.h>
#define SERVER_PORT 8000
#define MAXLINE 1500
int main()
{
        printf("server_udp\n");
        int sockfd, i;
        ssize_t len;
        struct sockaddr_in serveraddr, clientaddr;
        char buf[MAXLINE], ipstr[INET_ADDRSTRLEN];
        socklen_t clientlen;

        sockfd = socket(AF_INET, SOCK_DGRAM, 0);

        bzero(&serveraddr, sizeof(serveraddr));
        serveraddr.sin_family = AF_INET;
        serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
        serveraddr.sin_port = htons(SERVER_PORT);

        bind(sockfd, (struct sockaddr *) &serveraddr, sizeof(serveraddr));
        while(1)
        {
                clientlen = sizeof(clientaddr);
                len = recvfrom(sockfd, buf, sizeof(buf), 0, (struct sockaddr *) &clientaddr, &clientlen);
                printf("client IP %s \t PROT%d\n", inet_ntop(AF_INET, &clientaddr.sin_addr.s_addr, ipstr, sizeof(ipstr)), ntohs(clientaddr.sin_port));

                i = 0;
                while (i < len)
                {
                        buf[i] = toupper(buf[i]);
                        i++;
                }
                sendto(sockfd, buf, len, 0,(struct sockaddr *)&clientaddr, sizeof(clientaddr));
        }
        close(sockfd);

        return 0;
}

