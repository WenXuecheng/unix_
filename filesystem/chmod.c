#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
int main(int argc,char *argv[]){
        if(argc < 3){
                printf("./chmod mode filename\n");
                exit(1);
        }
        if (access(argv[2],F_OK)<0){
                perror(argv[2]);
                exit(1);
        }
        int mode;
        mode = strtol(argv[1],NULL,8);
        chmod(argv[2],mode);
        return 0;
}
