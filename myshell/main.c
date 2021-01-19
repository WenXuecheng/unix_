#include "myfun.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
int main(void)
{
        char input[100] = {0};
        while(1)
        {
                printf("wen>>");
                fflush(stdout);
                char argv[100][100]={0};
                fgets(input,99,stdin); 
                if (strcmp(input,"quit\n")==0)
                        break; 
                processor(input ,argv);
                Fork_do(argv);
        }
        return 0;
}
