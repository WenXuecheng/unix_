#include <stdio.h>
int main(void)
{
        char* p[5]={"how","are","you","li","ming"}   ;
        printf("%s\n",*p);
        printf("%s\n",*(p+1));
        return 0;


}
