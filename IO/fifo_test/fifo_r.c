#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
void sys_err(char *str,int  perrorno)
{
        perror(str);
        exit(perrorno);
}
int main(int argc , char *argv[]){

        int fd,len;
        char buf[1024];
        if(argc < 2 )
        {
               printf("./a.out fifoname\n"); 
               exit(1);
        }
        fd = open(argv[1],O_RDONLY|O_NONBLOCK);
        if (fd < 0){
                sys_err("open",1);
        }
        len=read(fd, buf ,sizeof(buf));
        printf("%d,%s\n",len,strerror(errno));
        write(STDOUT_FILENO,buf,len);
        close(fd);
        return 0;
}
