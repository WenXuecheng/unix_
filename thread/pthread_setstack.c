#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <error.h>
#include <string.h>
#define size 0x800000 
void *th_fnc(void *arg)
{
        int n=3;
        while(n--)
        {
                printf("n=%d\n",n);
                sleep(1);
        }
}
int main(void)
{
        pthread_t tid;
        int err, detachstate,i=1;
        pthread_attr_t attr;
        void *stackaddr;
        size_t stacksize;


        pthread_attr_init(&attr);

        pthread_attr_getstack(&attr, &stackaddr, &stacksize);
        printf("stackaddr = %p\n",stackaddr);
        printf("stackzie = %lu\n",stacksize);

        pthread_attr_getdetachstate(&attr, &detachstate);
        if(detachstate == PTHREAD_CREATE_DETACHED)
                printf("thread detached\n");
        else if(detachstate == PTHREAD_CREATE_JOINABLE)
                printf("thread join\n");
        else 
                printf("thread unknown\n");
        pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
        while(1){
                if((stackaddr = malloc(size)) == NULL){
                        perror("malloc");
                        exit(1);
                }

                stacksize = size;
                pthread_attr_setstack(&attr, stackaddr, stacksize);
                pthread_attr_getstack(&attr, &stackaddr, &stacksize);
                printf("stackaddr = %p\n",stackaddr);
                printf("stackzie = %lu\n",stacksize);
                err = pthread_create(&tid, &attr, th_fnc, NULL);
                if(err != 0){
                        printf("%s\n",strerror(err));
                        exit(1);
                }
                printf("%d\n",i++);
        }
        
        pthread_attr_destroy(&attr);
        return 0;
}
