#include "myfun.h"
int main(int argc, char *argv[])
{
        list *li = creat_list();
        change_list(li,1,"wen","fang","ok");
        show_list(li);
        add_one_in_list(li,2,"fang","wen","return");
        show_list(li);
        if (find_one_in_list(li,"fang") == 0) 
                del_one_in_list(li,"fang");
        show_list(li);
        printf("sdfasa");
        return 0;
}
