#include <stdio.h>
#include <stdlib.h>
struct STU{
        int a;
        char sex;
};
typedef struct STU STU;
int main(void )
{
        STU *stu,*stuu;
        STU sttu;
        stuu = calloc(1,sizeof(STU)); 
        printf("STU:%ld,stu:%ld,stuu:%ld,sttu:%ld",sizeof(STU),sizeof(stu),sizeof(stuu),sizeof(sttu));
        return 0;
}
