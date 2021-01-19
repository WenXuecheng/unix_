#include <stdio.h>
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

        int fd;
        char buf[] = "hello xwp\n";
        if(argc < 2 )
        {
               printf("./a.out fifoname\n"); 
               exit(1);
        }
        if (fd = open(argv[1],O_WRONLY) < 0)
                sys_err("open O_NONBLOCK",3);
        if (fd < 0){
                sys_err("open",1);
        }
        printf("eeeee");
        write(fd, buf ,strlen(buf));
        printf("wwwwwww");
//        write(STDOUT_FILENO, buf ,strlen(buf));
        close(fd);
        return 0;
}
