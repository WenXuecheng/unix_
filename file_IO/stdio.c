#include <sys/stat.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

int main(void )
{
        int flags,len;
        char buf[100];
        flags = fcntl(STDIN_FILENO,F_GETFL);
        flags |= O_NONBLOCK;
        fcntl(STDIN_FILENO,F_SETFL,flags);
        while(1)
        {
                len = read(STDIN_FILENO,buf,sizeof(buf));
                write(STDOUT_FILENO,buf,len);
                printf("len:%d\n",len);
                sleep(1);
        }
        return 0;

}
