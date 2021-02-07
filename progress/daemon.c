/*守护进程模型*/
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
void sys_err(const char *err)
{
        perror(err);
        exit(1);
}
void daemonize(void)
{
        pid_t pid;
        if((pid = fork())<0)
                sys_err("fork");
        else if (pid >0)
                exit(0);
        setsid();
        if(chdir("/")<0)
        {
                sys_err("chdir");
        }
        umask(0);
        close(0);
        open("/dev/null", O_RDWR);
        dup2(0, 1);
        dup2(0, 2);
}
int main(void)
{
        daemonize();
        while(1)
                ;
}
