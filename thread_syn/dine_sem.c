// chu shi hua mutex , xian chu shi hua hao mutex zai shi yong 
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <semaphore.h>
sem_t sem[5];

void err_pthread(int ret, char *str)
{
        if(ret != 0)
        {
                fprintf(stderr,"%s:%s\n",str,strerror(ret));
                //pthread_exit(NULL);
                exit(1);
        }
}
void sys_err(char *str)
{
        perror(str);
        exit(1);
}
#define DELAY (sleep(rand() % 3))
void *thread_func(void *arg)
{
        long i = (long) arg;

        while(1)
        {
               /* if (i == 4)
                {
                        printf("thread No.%ld thinking\n",i+1);
                        DELAY ;
                        printf("thread No.%ld hungry\n",i+1);
                        sem_wait(&sem[(i+1 ) % 5]);
                        DELAY ;
                        sem_wait(&sem[i]);
                        printf("thread No.%ld eating\n",i+1);
                        DELAY ;
                        sem_post(&sem[i]);
                        sem_post(&sem[(i+1 ) % 5]);
                        DELAY ;
                }
                else {*/
                        printf("thread No.%ld thinking\n",i+1);
                        DELAY ;
                        printf("thread No.%ld hungry\n",i+1);
                        sem_wait(&sem[i]);
                        DELAY ;
                        sem_wait(&sem[(i+1 ) % 5]);
                        printf("thread No.%ld eating\n",i+1);
                        DELAY ;
                        sem_post(&sem[(i+1 ) % 5]);
                        sem_post(&sem[i]);
                        DELAY ;
                //}

        }
        
        return NULL;
}
int main(void) 
{
        long i;
        int ret;
        pthread_t tid[5];
        //init sem and threads
        for(i = 0; i<5;i++)
        {
               ret = sem_init(&sem[i], 0, 1);
               if(ret != 0)
                       sys_err("mutex init");
        }
        for(i=0; i<5; i++)
        {
               ret = pthread_create(&tid[i], NULL, thread_func, (void *) i);
               if(ret != 0)
                       err_pthread(ret, "thread_create");
        //       printf("tid[%ld] = %lu\n",i,tid[i]);
        }

        for(i=0;i<5;i++)
        {
                int r;
                r=pthread_join(tid[i],NULL);
                if (r!=0)
                        printf("failed join!\n");
                else
                        printf("thread No.%ld\n",i);
        }
        for(i = 0;i<5;i++)
        {
                sem_destroy(&sem[i]);
                printf("%ld had been destoyed\n",i);
        }
        return 0;
}
