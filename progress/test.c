#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
int main(void )
{
        int fd = open("~/Desktop/test/new",O_RDONLY);
        if(fd == -1)
                printf("bad fd\n");
        char buf[1024]={0};
        read(fd,buf,sizeof(buf));
        printf("%s \n",buf);
}
