#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include "myfun.h"
extern int errno;
void sys_err(char *name ,int errorno)
{
        char buf[1024] = {0}; 
        sprintf(buf,"%s : %s\n",name,strerror(errno));
        write(1,buf,strlen(buf));
        exit(errorno);
        return ;
}
list *creat_list(void)
{
        list *li = calloc(1,sizeof(list));
        li->next = NULL; 
        return li;        
}

void change_list(list *li ,int date ,char *filename)
{
        li->date = date;
        strcpy(li->filename ,filename);
        return ;
}
void show_list(list *li)
{
        list *p = li;
        char str[5000]={0};

        while(p)
        {
                sprintf(str,"date:%d,filename:%s\n",p->date,p->filename);
                write(1,str,strlen(str));
                p=p->next;
        }
        return ;
}
void add_one_in_list(list *li,int date,char *filename)
{
        list *tem,*p = li;
        tem = creat_list();
        while(p->next)
        {
                p=p->next;
        }
        tem->next = p->next;
        p->next = tem;
        change_list(tem, date, filename);

}
int del_one_in_list(list *li ,char *filename)
{
        list *p = li;
        while(p)
        {
                if(p->next == NULL)
                        return -1;
                if(strcmp(p->next->filename,filename) == 0)
                        break;
                p = p->next;
        }
        list *temp = p->next;
        if (p->next->next == NULL)
                p->next = NULL;
        else 
                p->next =p->next->next;

        free(temp);
        return 0;


}
int find_one_in_list(list *li ,char *filename)
{
        list *p=li;
        while(p)
        {
                if(strcmp(p->filename,filename) == 0)
                        return p->date;
                p = p->next;
        }
        return -1;

}
int long_list(list *li)
{
        int i=0;
        list *p = li;
        while(p)
        {
                i +=1;
                p=p->next;
        }
        return i;
}
