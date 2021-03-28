#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h> 
#include <ctype.h>
#define SERVER_PORT 8000
#define MAXLINE 1024
int main(void)
{
        struct sockaddr_in serveraddr, clienaddr;
        int sockfd, addrlen, confd, i, len, pid;
        char ipstr[128], buf[MAXLINE];
        //1,socket 
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        //2.bind 
        bzero(&serveraddr, sizeof(serveraddr));
        serveraddr.sin_family = AF_INET;
        serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
        serveraddr.sin_port = htons(SERVER_PORT);
        bind(sockfd, (struct sockaddr *) &serveraddr, sizeof(serveraddr));
        //3.listen
        listen(sockfd, 128);
        //4.accept
        while(1){
                addrlen = sizeof(clienaddr);
                confd = accept(sockfd,(struct sockaddr *) &clienaddr, &addrlen);
                // out put clien ip and port 
                printf("clien ip %s\tport %d\n",
                                inet_ntop(AF_INET, &clienaddr.sin_addr.s_addr,ipstr,sizeof(ipstr)),
                                ntohs(clienaddr.sin_port));
                // duo jincheng
                pid = fork();
                if(pid == 0 )
                {
                        close(sockfd);
                        while(1){
                                len = read(confd, buf, sizeof(buf));
                                i = 0;
                                while (i < len)
                                {
                                        buf[i] = toupper(buf[i]);
                                        i++;
                                }
                                write(confd, buf, len);
                        }
                        close(confd);
                }
                else if(pid > 0)
                {
                        close(confd);
                }
        }
        close(sockfd);
        
}
