#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h> 
#include <sys/stat.h>
#include <fcntl.h>
#define SERVER_PORT 8000
#define MAXLINE 4096

int main(void)
{
        struct sockaddr_in serveraddr;
        int confd, len;
        char buf[MAXLINE],ipstr[] = "192.168.1.105";
        //1. socket
        confd = socket(AF_INET, SOCK_STREAM, 0);
        //2. init add
        bzero(&serveraddr, sizeof(serveraddr));
        serveraddr.sin_family = AF_INET;
        // set add
        inet_pton(AF_INET, ipstr, &serveraddr.sin_addr.s_addr);
        serveraddr.sin_port = htons(SERVER_PORT);
        //3. connect server
        connect(confd,(struct sockaddr *) &serveraddr, sizeof(serveraddr));
        //4. process data 
        while(fgets(buf,sizeof(buf), stdin))
        {

                write(confd, buf, strlen(buf));
                len = read(confd, buf, sizeof(buf));
                write(STDOUT_FILENO, buf, len);
        }
        //5. close
        close(confd);
        return 0;
}
