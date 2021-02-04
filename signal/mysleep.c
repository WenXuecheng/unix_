#include <signal.h>
#include <unistd.h>
#include <stdio.h>
void do_sig(int n){}
unsigned int mysleep(unsigned int n)
{
        struct sigaction newact, oldact;
        sigset_t newmask, oldmask, suspmask; 
        unsigned int unslept;

        newact.sa_handler = do_sig;
        sigemptyset(&newact.sa_mask);
        newact.sa_flags = 0;
        sigaction(SIGALRM, &newact, &oldact);

        sigemptyset(&newmask);
        sigaddset(&newmask, SIGALRM);
        sigprocmask(SIG_BLOCK, &newmask, &oldmask);

        alarm(n);

        suspmask = oldmask;
        sigdelset(&oldmask,SIGALRM);
        sigsuspend(&suspmask);

        unslept = alarm(0);
        sigaction(SIGALRM, &oldact, NULL);

        sigprocmask(SIG_SETMASK, &oldmask, NULL);
        return unslept;
}
int main(void)
{
        while(1)
        {
                mysleep(2);
                printf("Two seconds passed\n");
        }
}
