#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
void *thr_fn1(void *arg)
{
        printf("thread 1 ruturning\n");
        return (void *) 1;
}
void *thr_fn2(void *arg)
{
        printf("thread 2 ruturning\n");
        pthread_exit((void *) 2);
}
void *thr_fn3(void *arg)
{
        while(1)
        {
                printf("thread 3 ruturning\n");
                sleep(1);
        }
}
int main(void)
{
        pthread_t tid;
        void *tret;

        pthread_create(&tid, NULL, thr_fn1, NULL);
        pthread_join(tid, &tret);
        printf("thread 1 exit code %ld\n", (long int )tret);

        pthread_create(&tid, NULL, thr_fn2, NULL);
        pthread_join(tid, &tret);
        printf("thread 2 exit code %ld\n", (long int )tret);

        pthread_create(&tid, NULL, thr_fn3, NULL);
        sleep(3);
        pthread_cancel(tid);
        pthread_join(tid, &tret);
        printf("thread 3 exit code %ld\n", (long int )tret);
        return 0;
}

