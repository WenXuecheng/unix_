/* deleted client[OPEN_MAX]   */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/epoll.h>
#include "wrap.h"
#include <unistd.h>

#define MAXLINE 80
#define SERV_PROT 8000
#define OPEN_MAX 1024

int main(int argc, char *argv[])
{
        int i, j, maxfd, maxi, listenfd, connfd, sockfd, efd;
        int nready, client[OPEN_MAX];
        ssize_t n;
        char buf[MAXLINE];
        char str[INET_ADDRSTRLEN];
        socklen_t cliaddr_len;
        struct sockaddr_in cliaddr, servaddr;
        struct epoll_event tep, ep[OPEN_MAX];

        listenfd = Socket(AF_INET, SOCK_STREAM, 0);

        bzero(&servaddr, sizeof(servaddr));
        servaddr.sin_family = AF_INET;
        servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
        servaddr.sin_port = htons(SERV_PROT);

        Bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

        Listen(listenfd, 20);

        efd = epoll_create(OPEN_MAX);
        if (efd == -1)
                perr_exit("epoll_create");
        tep.events = EPOLLIN;
        tep.data.fd = listenfd;
        if (epoll_ctl(efd, EPOLL_CTL_ADD, listenfd, &tep) == -1)
                perr_exit("epoll_ctl");

        for(;;)
        {
                nready = epoll_wait(efd, ep, OPEN_MAX,-1);
                if (nready < 0)
                {
                        perr_exit("epoll_wait");
                }
                for(i = 0; i< nready ; i++)
                {
                        if(!(ep[i].events & EPOLLIN))
                                continue;
                        if(ep[i].data.fd == listenfd)
                        {
                                cliaddr_len = sizeof(cliaddr);
                                connfd = Accept(listenfd, (struct sockaddr *)&cliaddr, &cliaddr_len);
                                printf("reccept from %s at PORT %d\n",inet_ntop(AF_INET,&cliaddr.sin_addr, str, sizeof(str)),ntohs(cliaddr.sin_port));
                                if (connfd == OPEN_MAX)
                                {
                                        fputs("too many clients\n",stderr);
                                        exit(1);
                                }
                                tep.events = EPOLLIN;
                                tep.data.fd = connfd;
                                if (epoll_ctl(efd, EPOLL_CTL_ADD, connfd, &tep) == -1)
                                        perr_exit("epoll_ctl");

                        }
                        else
                        {
                                sockfd = ep[i].data.fd;
                                n = Read(sockfd, buf, MAXLINE);
                                if(n == 0)
                                {
                                        if (epoll_ctl(efd, EPOLL_CTL_DEL, sockfd, NULL) == -1)
                                                perr_exit("epoll_ctl");
                                        Close(sockfd);
                                        printf("client[%d] closed connection\n",j);
                                }
                                else
                                {
                                        for(j = 0; j < n; j++)
                                        {
                                                buf[j] = toupper(buf[j]);
                                        }
                                        Writen(sockfd, buf, n);
                                }
                        }
                }
        }
        Close(listenfd);
        close(efd);
        return 0;

}
