#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <semaphore.h>
pthread_mutex_t mutex[5];
pthread_cond_t cond[5];
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
                pthread_mutex_lock(&mutex[i]);
                printf("thread No.%ld thinking\n",i+1);
                DELAY ;
                printf("thread No.%ld hungry\n",i+1);
                DELAY ;
                pthread_cond_wait(&cond[i], &mutex[i]);
                pthread_mutex_lock(&mutex[(i + 1) % 5]);
                printf("thread No.%ld eating\n",i+1);
                DELAY ;
                pthread_mutex_unlock(&mutex[(i + 1) % 5]);
                pthread_mutex_unlock(&mutex[i]);
                DELAY ;

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
               ret = pthread_mutex_init(&mutex[i], NULL);
               if(ret != 0)
                       sys_err("mutex init");
        }
        for(i = 0; i<5;i++)
        {
                pthread_cond_init(&cond[i], NULL);
        }
        for(i=0; i<5; i++)
        {
               ret = pthread_create(&tid[i], NULL, thread_func, (void *) i);
               if(ret != 0)
                       err_pthread(ret, "thread_create");
        //       printf("tid[%ld] = %lu\n",i,tid[i]);
        }
        int who;
        while(1)
        {
                sleep(5);
                
                who=rand() % 5;
                printf("thread No.%d start \n",who+1);
                pthread_cond_signal(&cond[who]);

        }

        return 0;
}
