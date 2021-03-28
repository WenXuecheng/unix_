#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h> 
#include <ctype.h>
#include <pthread.h>
#include "wrap.h"
#define SERVER_PORT 8001
#define MAXLINE 1024
struct s_info {
        struct sockaddr_in cliaddr;
        int confd;
};
void *do_work(void *arg)
{
        int n,i;
        struct s_info *ts = (struct s_info *) arg;
        char buf[MAXLINE],str[INET_ADDRSTRLEN];

        pthread_detach(pthread_self());
        while(1)
        {
                n = Read(ts->confd, buf, MAXLINE);
                if(n==0)
                        //break;
                        continue;
                printf("received from %s at PORT %d\n",
                                inet_ntop(AF_INET, &(*ts).cliaddr.sin_addr, str, sizeof(str)), 
                                ntohs((*ts).cliaddr.sin_port));
                for(i = 0;i <  n ; i++)
                {
                        buf[i] = toupper(buf[i]);
                }
                Write(ts->confd, buf, n);
        }
        Close(ts->confd);
}
int main(void)
{
        struct sockaddr_in serveraddr, clienaddr;
        int sockfd, addrlen, confd, i, len, pid;
        char ipstr[128], buf[MAXLINE];
        pthread_t tid;
        struct s_info ts[383];
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
        printf("Accepting connections .....\n");
        while(1){
                addrlen = sizeof(clienaddr);
                confd = accept(sockfd,(struct sockaddr *) &clienaddr, &addrlen);
                ts[i].cliaddr = clienaddr;
                ts[i].confd = confd;
                pthread_create(&tid, NULL, do_work, (void*)&ts[i]);
                i++;

        }
        return 0;
        
}
