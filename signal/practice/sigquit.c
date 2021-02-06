#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <stdlib.h>
void do_sig(int signo)
{
        printf("in signal\n");
        while(1)
        {
                printf("in signal in while\n");
                sleep(1);
        }
}
void sys_err(const char *err, const int errno)
{
        perror(err);
        exit(1);
}
int main(void)
{
        struct sigaction act;
        act.sa_handler = do_sig;
        sigemptyset(&act.sa_mask);
        sigaddset(&act.sa_mask, SIGQUIT);
        act.sa_flags = 0;
        sigaction(SIGINT, &act, NULL);
        while(1)
        {
                printf("in main\n");
                sleep(1);
        }
        return 0;

}
