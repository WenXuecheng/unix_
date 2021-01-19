#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
int main(void){
        int fd[2];
        char str[1024]= "hello itcast";
        pid_t pid;
        if (pipe(fd) < 0)
        {
                perror("pipe");
                exit(1);
        }
        pid = fork();
        if (pid > 0)
        {
                //在父进程中
//                close(fd[0]);
                char str1[] = "p write to child";
                char buf1[1024],buf11[2048];
                sleep(5); 
                write(fd[1],str1,strlen(str1));
                wait(NULL);

                
        }
        else if (pid == 0 ) {
                int len ;
                char buf[1024];
                close(fd[1]);
                int flags = fcntl(fd[0], F_GETFL);
                flags |= O_NONBLOCK;
                fcntl(fd[0],F_SETFL,flags);
tryagain:
                len = read(fd[0],buf,sizeof(buf));
                if (len == -1)
                {
                        if(errno == EAGAIN){
                                write(STDOUT_FILENO,"try again\n",10);
                                sleep(1);
                                goto tryagain;
                        }
                        else{
                                perror("read");
                                exit(1);
                        }
                }
                write(STDOUT_FILENO, buf , len);
                close(fd[0]);

        }
        else {
                perror("fork");
                exit(1);
        }
        
        return 0;
}
