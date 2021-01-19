#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>



int main(void){
        close(STDOUT_FILENO);
        int fd = open("hello.t",O_WRONLY|O_CREAT,0644);
        printf("%d\n",fd);
        printf("i'm here!\n");
        fflush(stdout);
        close(fd);
        return 0;
}
