#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
pthread_mutex_t mutex[5];
pthread_mutex_t out_mutex = PTHREAD_MUTEX_INITIALIZER;

void mutex_printf(long i, long ii)
{
        pthread_mutex_lock(&out_mutex);
        fprintf(stdout,"%lu thread No.%ld got No.%ldchopsticks\n",pthread_self(),i, ii);
        pthread_mutex_unlock(&out_mutex);
        return ;
}

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
void *thread_func(void *arg)
{
        long ii = (long) arg;
        if(ii==4)
        {
                pthread_mutex_lock(&mutex[0]);
                //mutex_printf(4,0);
                pthread_mutex_lock(&mutex[4]);
                //mutex_printf(4,4);
                fprintf(stdout,"%lu thread No.%d got No.%d and No.%d chopsticks\n",pthread_self(), 4, 4, 0);
                usleep(1000);
                pthread_mutex_unlock(&mutex[0]);
                pthread_mutex_unlock(&mutex[4]);
                usleep(1000);
        }
        if(ii ==0){
        pthread_mutex_lock(&mutex[0]);
        //mutex_printf(ii,ii);
        //mutex_printf(ii,ii);
        pthread_mutex_lock(&mutex[1]);
        //mutex_printf(ii,(ii+1)%5);
        //        fprintf(stdout,"thread No.%ld got No.%ld\n",ii,(ii+1)%5);
        //mutex_printf(ii,ii+1);
                        
        //pthread_mutex_lock(&out_mutex);
        fprintf(stdout,"%lu thread No.%d got No.%d and No.%d chopsticks\n",pthread_self(), 0, 0, 1);
        //pthread_mutex_unlock(&out_mutex);
        //sleep(rand() % 5);
        usleep(1000);
        
        pthread_mutex_unlock(&mutex[1]);
        pthread_mutex_unlock(&mutex[0]);
        usleep(1000);
        }
        if(ii ==1){
                pthread_mutex_lock(&mutex[1]);
                pthread_mutex_lock(&mutex[2]);
                fprintf(stdout,"%lu thread No.%d got No.%d and No.%d chopsticks\n",pthread_self(), 1, 1, 2);
                usleep(1000);
                pthread_mutex_unlock(&mutex[1]);
                pthread_mutex_unlock(&mutex[2]);
                usleep(1000);
        } 
        if(ii ==2){
                pthread_mutex_lock(&mutex[2]);
                pthread_mutex_lock(&mutex[3]);
                fprintf(stdout,"%lu thread No.%d got No.%d and No.%d chopsticks\n",pthread_self(), 2, 2, 3);
                usleep(1000);
                pthread_mutex_unlock(&mutex[2]);
                pthread_mutex_unlock(&mutex[3]);
                usleep(1000);
        } 
        if(ii ==3){
                pthread_mutex_lock(&mutex[3]);
                pthread_mutex_lock(&mutex[4]);
                fprintf(stdout,"%lu thread No.%d got No.%d and No.%d chopsticks\n",pthread_self(), 3, 3, 4);
                usleep(1000);
                pthread_mutex_unlock(&mutex[4]);
                pthread_mutex_unlock(&mutex[3]);
                usleep(1000);
        } 
        //fprintf(stdout,"%lu thread No.%ld dt No.%ld and No.%ld chopsticks\n",pthread_self(), ii, ii, (ii + 1) % 5);
        return NULL;
}
int main(void) 
{
        while(1){
        long i;
        int ret;
        pthread_t tid[5];
        //init mutex and threads
        for(i = 0; i<5;i++)
        {
               ret = pthread_mutex_init(&mutex[i], NULL);
               if(ret != 0)
                       sys_err("mutex init");
        }
        for(i=0; i<5; i++)
        {
               ret = pthread_create(&tid[i], NULL, thread_func, (void *) i);
               if(ret != 0)
                       err_pthread(ret, "thread_create");
               printf("tid[%ld] = %lu\n",i,tid[i]);
               //pthread_detach(tid[i]);
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
                pthread_mutex_destroy(&mutex[i]);
                printf("%ld had been destoyed\n",i);
        }
        }
        return 0;
}
