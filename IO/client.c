#include "myfun.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
int main(int argc ,char *argv[])
{
        list *li;
        int len,fdserver;
        if (argc < 2 )
        {
                printf("client name");
                exit(1);
        }
        if ((fdserver = open(FIFO,O_WRONLY))< 0)
                sys_err("open FIFO",2);
        if (strlen(argv[1])>4)
        {
                printf("name too long\n");
                exit(1);
        }

        li = creat_list();
        change_list(li ,1,argv[1],"0","0");
        printf("li:%ld,list:%ld\n",sizeof(li),sizeof(list));
        if(write(fdserver,li,sizeof(list)) < 0)
                sys_err("login",3);
        show_list(li);
        be_nonblock(STDOUT_FILENO);
        while(1)
        {
                read_from_server(argv[1]);
                if (read_from_user(li,fdserver))
                        printf("Invaild input!\n");

                if(li->id == 4)
                {
                        close(fdserver);
                        printf("see you\n");
                        return 0;
                }
                sleep(1);
        }
        return 0;
}
