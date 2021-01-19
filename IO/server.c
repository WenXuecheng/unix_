#include "myfun.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
int main(int argc,char *argv[])
{
        int fdserver,len,flag;

        list *login_head;
        login_head = creat_list();
        while(1)
        {
                flag = mkfifo(FIFO,0777);
                if (flag < 0)
                        if (errno != EEXIST)
                                sys_err("mkfifo",1);
                break;
        }
        if ((fdserver = open(FIFO,O_RDONLY|O_NONBLOCK))<0)
                sys_err("open fifo",2);
        while(1)
        {
                list *li;
                li = creat_list();
                if((len = read(fdserver,li,sizeof(list))) < 0)
                {
                        if (errno != EAGAIN)
                                sys_err("server read",3);
                }
                resolve(li,login_head);
                sleep(1);                
                free(li);
        }
        close(fdserver);
        unlink(FIFO);

        return 0;
}
