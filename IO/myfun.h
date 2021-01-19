#ifndef __MYFUN_H_
#define _MYFUN_H_
#define FIFO "./myfifo"
struct list{
        int id;
        char src[5];
        char dest[5]; 
        char data[1000];
        struct list  *next;
};
typedef struct list list; 
void sys_err(char *name,int perrorno);
list *creat_list(void);
void show_list(list *li);
void change_list(list *li ,int id , char *src ,char *dest , char *data);
void add_one_in_list(list *li,int id ,char *src ,char *dest ,char *data);
void del_one_in_list(list *li ,char *src);
int find_one_in_list(list *li ,char *src);
void resolve(list *li, list *login);
void read_from_server(char *client_fifo);
int read_from_user(list *li , int fdserver);
void be_nonblock(int fd);
#endif
