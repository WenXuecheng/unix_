#ifndef __MYFUN_H_
#define _MYFUN_H_
struct list{
        int date;
        char filename[1024];
        struct list  *next;
};
typedef struct list list; 
void sys_err(char *name,int errorno);
list *creat_list(void);
void show_list(list *li);
void change_list(list *li ,int date, char *filename);
void add_one_in_list(list *li,int date ,char *fiename);
int del_one_in_list(list *li ,char *filename);
int find_one_in_list(list *li ,char *filename);
int long_list(list *li);
#endif
