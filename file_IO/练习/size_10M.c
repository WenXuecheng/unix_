#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>


int main(int argc, char *argv[]){
        if (argc<2){
                printf("input the name ");
                exit(2);
        }
        int fd = open(argv[1],O_CREAT|O_RDWR,0644);
        if(fd < 0){
                perror("open ");
                exit(1);
        }
        lseek(fd,0x9FFFFF,SEEK_SET);
        write(fd,"a",1);
        close(fd);
        return 0;
}
