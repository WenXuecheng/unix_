#include <stdio.h>
#include <errno.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
pid_t pid;
void sys_err(const char *str)
{
        perror(str);
        exit(1);
}
void do_sig(const int signo)
{
        static int n = -1;
        static int m = 0;
        n +=2;
        m +=2;
        if(n==99)
        {
                printf("parent done!\n");
                return ;
        }
        if(m==100)
        {
                printf("child done!\n");
                return ;
        }
        if (signo == SIGUSR1)
        {
                printf("child %d : %d\n",getpid(),m);
                kill(getppid(),SIGUSR2);
        }
        else if (signo == SIGUSR2)
        {
                printf("parent %d : %d\n",getpid(),n);
                kill(pid,SIGUSR1); 
        }

}
int main(void)
{
        struct sigaction act;
        act.sa_handler = do_sig;
        sigemptyset(&act.sa_mask);
        act.sa_flags = 0;
        sigaction(SIGUSR1,&act,NULL); 
        sigaction(SIGUSR2,&act,NULL); 
        if((pid = fork()) < 0)
                sys_err("fork");
        else if(pid > 0)
        {

                do_sig(SIGUSR2);
                while(1)
                        ; 
        }
        else if(pid == 0)
        {
                while(1)
                        ;
        }
        return 0;
}
