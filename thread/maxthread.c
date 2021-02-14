#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
void *th_fun(void *arg)
{
        while(1)
                sleep(1);
}
int main(void )
{
        pthread_t tid;
        long int i=1,err;
        
        while(1)
        {
                err = pthread_create(&tid, NULL, th_fun, NULL);
                if (err !=0)
                {
                        printf("%s\n",strerror(err));
                        sleep(10000);
                }
                printf("num : %ld\n",i++);
        }
        return 0;

}
