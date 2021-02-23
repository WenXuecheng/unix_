#include <stdlib.h> 
#include <pthread.h> 
#include <stdio.h> 
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>

#define NUM 5
void err_pthread(int ret, char *str)
{
        if(ret !=0)
        {
                fprintf(stderr, "%s:%s\n",str,strerror(ret));
                pthread_exit(NULL);
        }
}
int queue[NUM];
sem_t blank_number, product_number;
void *produser(void *arg)
{
        int p=0;
        while(1)
        {
                sem_wait(&blank_number);
                queue[p] = rand() % 1000 + 1;
                printf("produse:%d\n",queue[p]);
                sem_post(&product_number);

                
                p = (p + 1) % NUM;
                sleep(rand()%5);
        }

        return 0; 
}
void *consumer(void *arg)
{
        int c=0;
        while(1){ 
                sem_wait(&product_number);
                printf("consume : %d\n",queue[c]);
                queue[c] = 0;
                sem_post(&blank_number);

                c = (c + 1) % NUM;
                sleep(rand()%5);
        }

        return 0; 
}

int main(int argc, char **argv)
{
        int ret;
        pthread_t pid, cid;
        sem_init(&blank_number, 0, NUM);
        sem_init(&product_number, 0, 0);
         
        srand(time(NULL));

        ret = pthread_create(&pid, NULL, produser, NULL);
        if (ret != 0)
                err_pthread(ret, "pthread_create produser");

        ret = pthread_create(&cid, NULL, consumer, NULL);
        if (ret != 0)
                err_pthread(ret, "pthread_create comsumer");

        pthread_join(pid, NULL);
        pthread_join(cid, NULL);

        sem_destroy(&blank_number);
        sem_destroy(&product_number);
        return 0;
}
