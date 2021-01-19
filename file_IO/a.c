#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

int main(int argc , char *argv[])
{
        int fd;
        char buf[1024] = "kfh";
        if (argc<2){
                printf("./app filename\n");
                exit(1);
        }
        fd = open("hao123.cc",O_RDWR);
        write(fd,buf, strlen(buf));
        printf("fd=%d\n",fd);
        close(fd);
        return 0;
}
