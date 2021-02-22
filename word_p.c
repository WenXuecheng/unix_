#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
void sys_err(char *str)
{
        perror(str);
        exit(1);
}
int main(int argc, char **argv)
{
        char buf[10000],str[1000][1000],strbuf[1000][1000],(*p)[1000] = str,*tmp; 
        int fd,n;
        if(argc == 2)
        {
                printf("%s\n",argv[1]);
                fd = open(argv[1],O_RDWR);
        }

        else
        {
                printf("file name!\n");
                exit(1);
        }
        if(fd == -1)
                sys_err("open");

        if((n = read(fd, buf, sizeof(buf))) == -1)
                sys_err("read");
        int i = 0;
        tmp = strtok(buf, "\n");
        while(tmp!=NULL)
        {
                strcpy(str[i], tmp);
                printf("%s\n",str[i]);
                tmp = strtok(NULL, "\n");
                i++;
        }
        int r,num=i;
        printf("%d\n",num);
        while(i--)
        {        
                printf("%s\n",str[i]);
                while(1)
                {
                        r = rand() % (num);
                        if(strbuf[r][0] == '\0')
                        {
                                strcpy(strbuf[r],str[i]);
                                break;
                        }
                }
        }
        lseek(fd, 0,SEEK_SET);
        while(num--)
        {
                
                printf("%s\n",strbuf[num]);
                sprintf(buf,"%s\n",strbuf[num]);
                write(fd, buf,strlen(buf));
        }
        close(fd);
        return 0;
}
