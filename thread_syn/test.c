#include <stdio.h>
union Data 
{
        int i;
        float f;
        char str[20];
}
int main(void )
{
        for(int i =5;i >0;i--)
        {
                printf("%d \n",i);
        }
        for(int i =5;i > 0;--i)
        {
                printf("%d \n",i);
        }
        int i=5;
        while (i--)
        {
                printf("----%d\n",i);
        }
        i=5;
        while (--i)
        {
                printf("*******%d\n",i);
        }
        return 0;
        union Data data;
        data.i = 5555;
        int q ;
        q = (int)data;
        printf("------->%d\n",q);
}
