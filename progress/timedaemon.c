/*每隔十秒在/tem/dameon.log中写入当前时间*/
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>
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
void run(void)
{
        int fd;
        char buf[1024]={0};
        time_t t;

        time(&t);
        ctime_r(&t, buf);

        if((fd = open("/tmp/dameon.log", O_WRONLY|O_CREAT|O_APPEND, 0666)) < 0)
                sys_err("open log");
        if((write(fd, buf, sizeof(buf))) < 0)
                sys_err("write log");

        close(fd);
}
int main(void)
{
        daemonize();
        while(1)
        {
                run();
                sleep(10);
        }
        return 0;
}
