/*编写监控/home/usr/目录下文件创建与更改的守护进程，日志文件放在/home/usr/ filechangelog*/
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include "myfun.h"
#include <string.h>
#include <dirent.h>
#include <time.h>
void daemonize(void)
{
        pid_t pid;
        if((pid = fork())<0)
                sys_err("fork",1);
        else if (pid >0)
                exit(0);
        setsid();
        if(chdir("/")<0)
        {
                sys_err("chdir",1);
        }
        umask(0);
        close(0);
        open("/dev/null", O_RDWR);
        dup2(0, 1);
        dup2(0, 2);
        int fdlog;
        fdlog = open("/home/wen/Desktop/log",O_WRONLY|O_CREAT|O_APPEND,0666);
        dup2(fdlog, 1);
        close(fdlog);
        char buf[100]={0}, tmp[1024] = {0};
        time_t t;
        time(&t);
        ctime_r(&t, buf);
        sprintf(tmp,"%sset daemon\n",buf);
        write(1,"**********\n",12);
        write(1,tmp,sizeof(tmp));
        
}
void run()
{
        int flag = 0;
        char *log = "/tmp/filechangelog";
        char *dir = "/home/wen/Desktop/test";

        //open log file 
        int fd;
        if ((fd = open(log,O_WRONLY|O_CREAT|O_APPEND,0666)) < 0)
                sys_err("open file log",1);

        //define statebuff
        struct stat stbuf;
        
        //define directory var 
        char name[1024]={0};
        struct dirent *dp;
        DIR *dfd;

        //define Node to save information of files
        static list *files;
        list  *tmp,*p;
        tmp = creat_list();

        //get time 
        char timebuf[100]={0};
        time_t t;
        time(&t);
        ctime_r(&t, timebuf);


        //walk in dir get tmp
        if((dfd = opendir(dir)) == NULL)
        {
                exit(-1);
        }
        while ((dp = readdir(dfd)) != NULL)
        {
                if((strcmp(dp->d_name,".")) ==0 | (strcmp(dp->d_name,"..") == 0))
                        continue;
                if(strlen(dir)+strlen(dp->d_name)+2 > sizeof(name))
                        exit(-1);
                else 
                {
                        sprintf(name, "%s/%s", dir, dp->d_name);
                        if((stat(name, &stbuf)) < 0)
                                sys_err("stat",1);
                        add_one_in_list(tmp, stbuf.st_mtime, name);
                }
        }
        //cmapare files 
        if (files == NULL)
                files = tmp;
        
        else
        {
                p = tmp;
                int t;
                strcpy(name,"These files was changed :");
                while(p->next)
                {
                        if((t=find_one_in_list(files, p->next->filename)) != -1 )
                        {
                                if(p->next->date != t)
                                {
                                        strncat(name, "  ",100);
                                        strncat(name,p->next->filename,102);
                                        flag = 1;
                                }
                        }
                        p=p->next;
                }
                strncat(name,"\n",102);
                p = tmp;
                strncat(name,"These files was added :",102);
                while(p->next)
                {
                        if((t=find_one_in_list(files, p->next->filename)) == -1)
                        {
                                strncat(name,"  ",102);
                                strncat(name,p->next->filename,102);
                                flag = 1;
                        }
                        p=p->next;
                }
                strncat(name,"\n",102);
                p = files;
                strncat(name,"These files was deleted :",102);
                while(p->next)
                {
                        if((t=find_one_in_list(tmp, p->next->filename)) == -1)
                        {
                                strncat(name,"  ",102);
                                strncat(name,p->next->filename,102);
                                flag = 1;
                        }
                        p=p->next;
                }
                strncat(name,"\n",102);
                files = tmp;
        }

        if(flag == 1)
        {
                char output[10000]={0};
                sprintf(output,"----->\n%s%s<-----\n",timebuf,name);
                write(fd,output,strlen(output));
        }
        close(fd);
        closedir(dfd);
        return ;

}
int main(void)
{
        daemonize();
        while(1)
        {
                run();
                sleep(60);
        }
}
