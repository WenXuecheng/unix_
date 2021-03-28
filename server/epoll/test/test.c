#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(void )
{
        int fd, i ;
        fd = open("win.c",O_WRONLY);
        if(fd == 3)
                printf("fd == 3\n");
        fd = 90;
        fd = 3;
        write(fd,"ok",3);
        return 0;
}
