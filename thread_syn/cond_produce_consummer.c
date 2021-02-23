#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>

struct msg
{
        int num;
        struct msg *next;
};

struct msg *head;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t has_data = PTHREAD_COND_INITIALIZER;

void err_pthread(int ret, char *str)
{
        if(ret !=0)
        {
                fprintf(stderr, "%s:%s\n",str,strerror(ret));
                pthread_exit(NULL);
        }
}

void *produser(void *arg)
{
        while(1){
        struct msg *mp = malloc(sizeof(struct msg));
        mp->num = rand()% 1000 + 1;
        printf("produser----------------%d\n",mp->num);

        pthread_mutex_lock(&mutex);

        mp->next = head;
        head = mp ;
        pthread_mutex_unlock(&mutex);

        pthread_cond_signal(&has_data);
        
        sleep(rand() % 3);
        }
        return NULL;
}

void *consumer(void *arg)
{
        while(1){
        struct msg *mp;

        pthread_mutex_lock(&mutex);

        if(head == NULL)
                pthread_cond_wait(&has_data, &mutex);

        mp = head;
        head = mp->next;

        pthread_mutex_unlock(&mutex);
        printf("consumer----------------%d\n",mp->num);
        
        free(mp);
        
        sleep(rand() % 3);
        }
        return NULL;
}
int main(int argc, char **argv)
{
        int ret;
        pthread_t pid, cid;
         
        srand(time(NULL));

        ret = pthread_create(&pid, NULL, produser, NULL);
        if (ret != 0)
                err_pthread(ret, "pthread_create produser");

        ret = pthread_create(&cid, NULL, consumer, NULL);
        if (ret != 0)
                err_pthread(ret, "pthread_create comsumer");

        pthread_join(pid, NULL);
        pthread_join(cid, NULL);
        return 0;
}
