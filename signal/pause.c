#include <stdio.h>
#include <signal.h>
#include <unistd.h>
void do_sig(int n)
{
        printf("in do_sig\n");

}
int mysleep(int n)
{
        signal(SIGALRM, do_sig);
        alarm(n);
        pause();
}
int main(void)
{
        struct sigaction act; 
        int i;

        act.sa_handler = do_sig;
 //       act.sa_handler = SIG_DFL;
        sigemptyset(&act.sa_mask);
        act.sa_flags = 0;

        sigaction(SIGUSR1, &act, NULL);

        i=pause();
        printf("pause i = %d\n",i);
 
//        mysleep(2);
        printf("hello\n");
        return 0;
}
