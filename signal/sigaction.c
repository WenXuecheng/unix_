#include <stdio.h>
#include <signal.h>
#include <unistd.h>
void do_sig(int num)
{
        int n=6;
        printf("I am do_sig\n");
        while(n--)
        {
                printf("num = %d \n",num);
                sleep(1);
        }
        
}
int main(void)
{
        struct sigaction act;
        act.sa_handler = do_sig;
        sigemptyset(&act.sa_mask);
        act.sa_flags = 0;
        sigaction(SIGINT,&act,NULL);
        while(1)
        {
                printf("***********\n");
                sleep(1);
        }
        return 0;
}

