#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(void)
{
        pid_t pid ;
        if((pid = fork()) < 0)
        {
                perror("fork");
                exit(1);
        }
        else if(pid == 0)
        {
                printf("child process PID is %d\n",getpid());
                printf("Group ID of child is %d\n",getpgid(0));
                sleep(5);
                printf("Group ID of child is changed to %d\n",getpgid(0));
                exit(0);
        }
        else if(pid > 0)
        {
                sleep(1);
                setpgid(pid,pid);

                sleep(5);

                printf("parent process PID is %d\n",getpid());
                printf("parent of parent process PID is %d\n",getppid());
                printf("Group ID of parent is %d\n",getpgid(0));
                setpgid(getpid(),getppid());
                printf("Group ID of parent is changed to %d\n",getpgid(0));
        }
}
