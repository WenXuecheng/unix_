#include <stdio.h>     
struct STU {
        int i;
        char sex;
//        struct STU *next;
};
typedef struct STU STU;
int main(void){
        STU stu;
        printf("%ld\n",sizeof(stu));
        return 0;
}
