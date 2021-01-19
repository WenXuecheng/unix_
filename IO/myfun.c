#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include "myfun.h"
void sys_err(char *name ,int perrorno)
{
        perror(name);
        exit(perrorno);
        return ;
}
list *creat_list(void)
{
        list *li = calloc(1,sizeof(list));
        li->next = NULL; 
        return li;        
}

void change_list(list *li ,int id ,char *src ,char *dest ,char *data)
{
        li->id = id;
        strcpy(li->src ,src);
        strcpy(li->dest ,dest);
        strcpy(li->data ,data);
        return ;
}
void show_list(list *li)
{
        list *p = li;
        while(p)
        {
                printf("id:%d,src:%s,dest:%s,data:%s\n",p->id,p->src,p->dest,p->data);
                p=p->next;
        }
        return ;
}
void add_one_in_list(list *li,int id ,char *src ,char *dest ,char *data)
{
        list *tem,*p = li;
        tem = creat_list();
        while(p->next)
        {
                p=p->next;
        }
        tem->next = p->next;
        p->next = tem;
        change_list(tem,id,src,dest,data);

}
void del_one_in_list(list *li ,char *src)
{
        list *p = li;
        while(strcmp(p->next->src,src))
                p = p->next;
        list *temp = p->next;
        if (p->next->next == NULL)
                p->next = NULL;
        else 
                p->next =p->next->next;

        free(temp);
        return ;


}
int find_one_in_list(list *li ,char *src)
{
        list *p=li;
        while(p)
        {
                if(strcmp(p->src,src) == 0)
                        return 0;
                p = p->next;
        }
        return -1;

}
void resolve(list *li,list *login)   //解析服务器接收到的数据
{
        int fdclient;
        switch (li->id) //根据数据包的id处理
        {
                case 1: //登录信息
                        add_one_in_list(login,li->id, li->src, li->dest,li->data);  //在链表中添加一个元素
                        if((mkfifo(li->src, 0644)) < 0)  //创建服务器与用户之间通信的管道
                                if (errno != EEXIST)
                                        sys_err("mkfifo",4);
                        break;
                case 2: //聊天
                        if(find_one_in_list(login, li->dest) <0)
                        {     //聊天包首先是查找用户是否在线
                                printf("The user is not login\n");
                                if((fdclient = open(li->src, O_WRONLY)) < 0) 
                                        sys_err("open userfifo",5);
                                write(fdclient, "Don't have this user\n", 21);
                                close(fdclient);
                                return ;  
                        }
                        char buff[1050] = {0};
                        printf("%s\n",li->dest);
                        if((fdclient = open(li->dest, O_WRONLY)) < 0) //如果存在，就打开对方的管道文件
                                sys_err("open userfifo",5);
                        printf("fdclient:%d\n",fdclient);
                        printf("fdclient\n");
                        sprintf(buff, "%s:%s\n", li->src, li->data);    //把要发给对方的数据写入buff内
                        printf("buff:%s\n",buff);
                        int l;
                        l=write(fdclient, buff, strlen(buff));
                        printf("write\n");
                        printf("l:%d\n",l);
                        //if((write(fdclient, buff, strlen(buff))) < 0)    //把buff写入对方的管道文件中，等待对方读取
                        ////   sys_err("write userfifo",5);
                        close(fdclient);
                        break;
                case 4: //退出
                        unlink(li->src);    //退出，把用户的管道文件删除
                        del_one_in_list(login, li->src);   //删除链表元素
                        break;
    }
        return ;
}
int read_from_user(list *li ,int fdserver)
{
        int len;
        char buf[1024]={0};
        char *dest_name;

        if ((len = read(STDIN_FILENO,buf,sizeof(buf))) < 0)
        {
                if (errno != EAGAIN)
                        sys_err("read from user",6);
        }
        else
        {
                if((strcmp(buf, "quit\n")) == 0||(strcmp(buf,"exit\n") == 0))
                {
                        li->id = 4;
                        write(fdserver,li,sizeof(list));
                        return 0;
                }
                if((len < 4) && (len > 0))
                        return -1;
                if(strlen((dest_name = strtok(buf, ":"))) > 4)
                        return -1;
                li->id = 2;
                strcpy(li->dest, dest_name);
                dest_name = strtok(NULL, ":");
                strcpy(li->data, dest_name);
                printf("im->src = %s, im->dest = %s, im->data = %s\n", li->src, li->dest, li->data);
                write(fdserver, li, sizeof(list));
        }
        return 0;
}

void read_from_server(char *client_fifo)
{
        int len,fdclient;
        char buf[1024]={0};
        if ((fdclient = open(client_fifo,O_RDONLY|O_NONBLOCK)) < 0)
        {
                if (errno == ENOENT)
                {
                        printf("链接服务器......\n");
                        return ;
                }
                sys_err("read from user",5);
        }
        sleep(1);
        if ((len = read(fdclient,buf,sizeof(buf))) < 0)
                if (errno != EAGAIN)
                        sys_err("read from server",5);
        write(STDOUT_FILENO,buf,len);
        close(fdclient);
        return ;
}
void be_nonblock(int fd)
{
        int flags ;
        if((flags = fcntl(fd,F_GETFL)) < 0)
                sys_err("fcntl",5);
        flags = flags|O_NONBLOCK;
        if(fcntl(fd,F_SETFL,flags) < 0)
                sys_err("fcntl",1);
}
