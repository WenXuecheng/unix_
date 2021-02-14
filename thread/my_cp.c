#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/mman.h>
typedef struct INFO
{
        int max;
        int num;
        size_t size;    
        char *sc_addr, *desc_addr;
        off_t file_size;
}Info;
void input_err(void)
{
        printf("sc,desc,num\n");
        exit(-1);
}
void sys_err(char *str)
{
        perror(str);
        exit(-1);
}
off_t size_of_file(int fd)
{
        struct stat statbuf;
        if(fstat(fd, &statbuf) < 0) 
                sys_err("size_of_file/stat");
        return statbuf.st_size;
}
void *thr_fn(void *arg)
{
        if (arg == NULL)
                sys_err("arg");
        Info *p = (Info *) arg;
        sleep(1);
        printf("thread No.%d ready\n",p->num);
        printf("max %d,num %d,file_size %ld,size %zu\n",p->max,p->num,p->file_size,p->size);
        
        size_t  offset =p->num * p->size; 
        printf("offset %zu\n",offset);
        if(p->num < p->max-1)
        {
                //printf("desc %zu,sc %zu,size%ld\n",(size_t)(p->desc_addr +offset),(size_t)(p->sc_addr + offset),(size_t) p->size);
                memcpy((p->desc_addr + offset),(p->sc_addr + offset), (size_t)p->size);
        }
        else if(p->num == p->max-1)
        {
                memcpy((p->desc_addr + offset),(p->sc_addr + offset), (size_t)(p->file_size - p->num * p->size));
        }
        printf("thread No.%d work done\n",p->num);
        
}
int main(int argc,char **argv)
{
        if(argc < 4)
                input_err();
        //set umask for files 
        umask(0);

        //get handler of sc and desc
        int sc_fd,desc_fd;
        if((sc_fd = open(argv[1],O_RDWR)) <0 )
                sys_err("open sc");
        if((desc_fd = open(argv[2],O_CREAT|O_RDWR, 0666)) <0 )
                sys_err("open desc");
        printf("size of %d\n",(int) size_of_file(sc_fd));
         
        // num of threads
        int num = atoi(argv[3]);

        //creat struct
        Info *info = (Info *) malloc(num*sizeof(Info));
        memset(info, 0, num*sizeof(Info));
        printf("struct INFO %zu\nInfo %zu\n",sizeof(struct INFO),sizeof(Info));

        //set frist struct 
        info[0].file_size = lseek(sc_fd, 0, SEEK_END);
        ftruncate(desc_fd,info[0].file_size);
        if(num > info[0].file_size)
        {
                printf("too many threads ,only start %d threads\n",num);
                num = info[0].file_size;
        }
        info[0].max = num;
        info[0].num = 0;
        info[0].size = info[0].file_size/num;
        info[0].sc_addr =  mmap(NULL,info[0].file_size,PROT_READ|PROT_WRITE,MAP_SHARED, sc_fd,0);
        info[0].desc_addr =  mmap(NULL,info[0].file_size,PROT_READ|PROT_WRITE,MAP_SHARED, desc_fd,0);
        for(int i = 1;i < num; i++)
        {
                info[i] = info[0];
                info[i].num = i;
        }
        printf("set info\n");
        for(int i =0 ;i <num;i++)
        {
                printf("info[%d],max %d,num %d,file_size %ld,size %zu\n",i,info[i].max,info[i].num,info[i].file_size,info[i].size);
        }
        if(info[0].file_size % num!=0)
                printf("remainder= %ld\n",info[0].file_size-(num-1)*info[0].size);

        //start threads
        pthread_t tid;
        while(num--)
        {
                pthread_create(&tid, NULL, thr_fn, (void *)&info[num]);
                pthread_detach(tid);
        }
        printf("main thread ending ! \n");
        pthread_exit(NULL);
}
