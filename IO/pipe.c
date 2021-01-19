#include <stdio.h>
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
                write(fd[1],str1,strlen(str1));
                sleep(5); 
                read(fd[0],buf1,sizeof(buf1));
                sprintf(buf11,"%s p copy\n",buf1);
                write(STDOUT_FILENO,buf11,strlen(buf11));
                wait(NULL);

                
        }
        else if (pid == 0 ) {
                int len ;
                char buf[1024];
                char buf22[2048];
                char str22[] = "child to p";
//                close(fd[1]);
                len = read(fd[0],buf,sizeof(buf));
                sprintf(buf22,"%s child copy\n",buf);
                write(STDOUT_FILENO, buf22 , strlen(buf22));
                sleep(1);
                write(fd[1],str22,strlen(str22));

        }
        else {
                perror("fork");
                exit(1);
        }
        
        return 0;
}
