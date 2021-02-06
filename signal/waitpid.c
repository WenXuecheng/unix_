#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
void sys_err(char *err)
{
        perror(err);
        exit(1);
}
void do_sig(int signo)
{
        /*   
         *   while(!(waitpid(0,NULL, WNOHANG)));
         */
        int status;
        pid_t pid ;
        while((pid = waitpid(0,&status, WNOHANG)) > 0)
        {
                if(WIFEXITED(status))
                        printf("child %d exit %d\n", pid, WEXITSTATUS(status));
                else if(WIFSIGNALED(status))
                        printf("child %d cancel signal %d\n", pid, WTERMSIG(status));
        }
}
int main(void)
{
        pid_t pid;
        int i;
        for(i = 1;i < 10; i++)
        {
                if((pid = fork()) == 0)
                        break;
                else if(pid < 0)
                        sys_err("fork");
        }
        if(pid == 0)
        {
                int n=19;
                while(n--)
                {
                        printf("child No.%d ID = %d\n",i,getpid());
                        sleep(1);
                }

        }
        else if(pid > 0)
        {
                struct sigaction act;

                act.sa_handler = do_sig;
                sigemptyset(&act.sa_mask);
                act.sa_flags = 0;
                sigaction(SIGCHLD, &act, NULL);
                while(1)
                {
                        printf("Parent ID = %d\n",getpid());
                        sleep(1);
                }
                
        }
        return 0;
}
