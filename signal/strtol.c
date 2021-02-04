#include <stdio.h>
#include <string.h>
int main(void)
{
        char buf[] = "hello world itcast wxc";
        char *save, *p;
        p = strtok_r(buf, " ", &save);
        printf("%s\n",p);
        
        while (p != NULL)
        {
                printf("%s\n",p);
                p = strtok_r(NULL, " ", &save);
        }
        return 0;
}
