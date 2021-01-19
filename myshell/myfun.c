#include "myfun.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

void sys_err(char *str ,int num)
{
        perror(str);
        exit(num);
}
void processor(char *input ,char argv[][100])
{
        char *p;
        int i=0;
        p = strsep(&input," ");
        while (p != NULL)
        {
                
                if(*p == '\0')
                        continue;
                strcpy(argv[i],p);
                p = strsep(&input," ");
                i+=1;
                if(p == NULL)
                        for(int j = 0;j<strlen(argv[i-1]);j++)
                                if (argv[i-1][j] == '\n')
                                        argv[i-1][j] = '\0';
        }
        //printf("processor\n");

        return ;
}

void Fork_do(char argv[][100])
{
        char (*p)[100]=argv;
        int flag=1;
        /*for(int i=0;i<99;i++)
        {
                if (p[i]==NULL)
                {
                        printf("p = NULL");
                        continue;
                }
                printf("p[%d]:%s\n",i,p[i]);
        }*/
        for(int i=0;i<100;i++)
        {
                if(strcmp(p[i],"<")==0 |strcmp(p[i],">")==0)
                        flag=2;
                if(strcmp(p[i],"|")==0)
                {
                        flag=3;
                        break;
                }
                if(p[i][0]=='\0')
                        break;

        }
        //printf("flag:%d\n",flag);
        if(flag==3)
        {
                //printf("flag 3 \n");
                Fork_three(argv);
        }
        if(flag == 2)
        {
                //printf("flag 2 \n");
                Fork_two(argv);
        } 
        if(flag == 1)
        {
                //printf("flag 1 \n");
                Fork_one(argv);
        }
        return ;
}

void Fork_one(char argv[][100])
{       
        int pid ,num;
        for(int i=0;i<100;i++)
        {
                if(argv[i][0]=='\0')
                {
                        num = i;
                        break;
                }
        }
        char * ps_argv[num+1];
        for(int i = 0;i<=num;i++)
        {
                ps_argv[i]=(char *)argv[i];
                if (i==num)
                        ps_argv[i]=NULL;
        }
        pid = fork();
        if (pid<0)
                sys_err("fork",1);
        if (pid == 0)
        {
                /*for(int i=0; i<(num+1);i++)
                {
                        if(ps_argv[i]==NULL)
                        {
                                printf("in flag1 ps_argv NULL\n");
                                continue;
                        }
                        printf("ps_argv in 1 :%s\n",ps_argv[i]);
                        
                }*/
                execvp(ps_argv[0],ps_argv);
                sys_err("exec",1);
        }
        else
                wait(NULL);
        return ;
}
void Fork_two(char argv[][100])
{       
        int pid ,num;
        for(int i=0;i<100;i++)
        {
                if(argv[i][0]=='\0')
                {
                        num = i;
                        break;
                }
        }
        char * ps_argv[num+1];
        for(int i = 0;i<=num;i++)
        {
                ps_argv[i]=(char *)argv[i];
                if (i==num)
                        ps_argv[i]=NULL;
        }
        pid = fork();
        if (pid<0)
                sys_err("fork",1);
        if (pid == 0)
        {
                //printf("NULL\n");
                int i=0;
                while(ps_argv[i]!=NULL)
                {
                        if(strcmp(ps_argv[i],"<")==0)
                        {
                                int fd ;
                                fd =open(ps_argv[i+1],O_RDONLY|O_CREAT,0666);
                                dup2(fd,STDIN_FILENO);
                                close(fd);
                                ps_argv[i]=NULL;
                                ps_argv[i+1]=NULL;
                                i+=2;
                                continue;
                        }
                        if(strcmp(ps_argv[i],">")==0)
                        {
                                int fd ;
                                fd =open(ps_argv[i+1],O_WRONLY|O_CREAT,0666);
                                dup2(fd,STDOUT_FILENO);
                                //close(fd);
                                ps_argv[i]=NULL;
                                ps_argv[i+1]=NULL;
                                i+=2;
                                continue;
                        }
                        i+=1;
                }
     //           for(int i = 0;i<=num;i++)
       //         {
         //               if(ps_argv[i]==NULL)
           //             {
             //                   printf("NULL\n");
               //         }
                 //       else
                   //             printf("%s\n",ps_argv[i]);
                //}              
                execvp(ps_argv[0],ps_argv);
                sys_err("exec",1);
        }
        else
                wait(NULL);
        return ;
}
void Fork_three(char argv[][100])
{       
        int pid ,num,num_p=0,j=0,pip_p[100]={0};
        for(int i=0;i<100;i++)
        {
                if(argv[i][0]=='\0')
                {
                        num = i;
                        break;
                }
        }
        char * ps_argv[num+1];
        for(int i = 0;i<=num;i++)
        {
                ps_argv[i]=(char *)argv[i];
                if (i==num)
                        ps_argv[i]=NULL;
        }
	for(int i =0;i<num;i++)
	{
		if (strcmp(ps_argv[i],"|")==0)
		{
			num_p+=1;
			pip_p[j]=i;
			j=j+1;
		}
	}
	//创建管道
	int pip_fd[2*num_p];
	for(int i=0;i<num_p;i++)
	{
		int fd[2];
		if(pipe(fd)<0)
			sys_err("pipe",1);
		pip_fd[2*i]=fd[0];
		pip_fd[2*i+1]=fd[1];
	}
	int i=0,d=0;
	//printf("num_P:%d\n",num_p);
tryagin:
	pid=fork();
	if(pid < 0)
		sys_err("fork",1);
	if(pid == 0)
	{
                //printf("child%d\n",i);
                if(i==0)
                {

                        //printf("sdf\n");
                        d = pip_p[i]+1;
                        char *r_argv[d];
                        for(int k=0;k<d;k++)
                        {
                                if(k==d-1)
                                {
                                        r_argv[k] = NULL;
                                        break;
                                }
                                if(strcmp(ps_argv[k],"<")==0)
                                {
                                        int fd1 ;
                                        fd1 =open(ps_argv[k+1],O_RDONLY|O_CREAT,0666);
                                        dup2(fd1,STDIN_FILENO);
                                        close(fd1);
                                        r_argv[k]=NULL;
                                        r_argv[k+1]=NULL;
                                        r_argv[k+2]=NULL;
                                        break;
                                }
                                r_argv[k] = ps_argv[k];
                        }

                        /*for(int i = 0;i<d;i++)
                        {
                                if(r_argv[i]==NULL)
                                {
                                        printf("NULL\n");
                                        continue;
                                }
                                printf("r_argv in 1 :%s\n",r_argv[i]);
                                
                        }*/
                        //close(pip_fd[0]);
                        if(dup2(pip_fd[2*i+1],STDOUT_FILENO)<0)
                                sys_err("dup2 1",1);
	                for(int i=0;i<num_p;i++)
	                {
		                close(pip_fd[2*i]);
		                close(pip_fd[2*i+1]);
	                }

                        execvp(r_argv[0],r_argv);
                }
                if(i==num_p)
                {
                        d =num - pip_p[i-1];
                        char *r_argv[d];
                        for(int k=1;k<=d;k++)
                        {
                                if(k==d)
                                {
                                        r_argv[k-1] = NULL;
                                        continue;
                                } 
                                r_argv[k-1] = ps_argv[k+pip_p[i-1]];
                        }
                        for(int k=0;k<d;k++)
                        {
                                
                                //printf("child1:%s\n",r_argv[k]);
                                //printf("leng r_argv in 1 :%d\n",d);
                                if(r_argv[k]==NULL)
                                        break;
                                if(strcmp(r_argv[k],">")==0)
                                {
                                        int fd1 ;
                                        fd1 =open(r_argv[k+1],O_WRONLY|O_CREAT,0666);
                                        if(dup2(fd1,STDOUT_FILENO)<0)
                                                sys_err("dup2 ",1);
                                        close(fd1);
                                        r_argv[k]=NULL;
                                        r_argv[k+1]=NULL;
                                        r_argv[k+2]=NULL;
                                        break;
                                }
                        }
                        /*for(int i = 0;i<d;i++)
                        {
                                if(r_argv[i]==NULL)
                                {
                                        printf("null\n");
                                        continue;
                                } 
                                printf("%s\n",r_argv[i]);
                                
                        }*/
                        //close(pip_fd[1]);
                        if(dup2(pip_fd[2*i-2],STDIN_FILENO)<0)
                                sys_err("dup2",1);
                        sleep(0.01);
                        //printf("------------------------\n");
	                for(int i=0;i<num_p;i++)
	                {
		                close(pip_fd[2*i]);
		                close(pip_fd[2*i+1]);
	                }
                        execvp(r_argv[0],r_argv);
                }
                /*else
                {
                        d = pip_p[i] - pip_p[i-1];
                        char *r_argv[d];
                        for(int k=1;k<=d;k++)
                        {
                                if(k==d)
                                {
                                        r_argv[k] = NULL;
                                        continue;
                                }
                                r_argv[k] = ps_argv[pip_p[i-1]+k];
                        }
                        dup2(pip_fd[2*i-2],STDIN_FILENO);
                        dup2(pip_fd[2*i+1],STDOUT_FILENO);
	                for(int i=0;i<num_p;i++)
	                {
		                close(pip_fd[2*i]);
		                close(pip_fd[2*i+1]);
	                }
                        execvp(r_argv[0],r_argv);
                }*/

	}
	if(pid > 0)
	{

                i=i+1;
                if(i<=num_p)
			goto tryagin;
                
                for(int i=0 ;i<num_p;i++)
                {
		        close(pip_fd[2*i]);
		        close(pip_fd[2*i+1]);
                }
                for(int i =0 ;i<=num_p;i++)
                {
                        wait(NULL);
                }
	}
	return ;



}
