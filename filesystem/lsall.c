#include <sys/types.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#define MAX_PATH 1024
void dirwalk(char *dir ,void (*fcn)(char *)){
        char name[MAX_PATH];
        DIR *dirp;
        struct dirent *direntbuf;
        if ((dirp = opendir(dir)) == NULL){
                fprintf(stderr,"can't open dir : %s",dir);
                return;
        }
        else{
                printf("--------\n");
                while((direntbuf = readdir(dirp)) != NULL){
                        if (strcmp(direntbuf->d_name,".") ==0 || strcmp(direntbuf->d_name,"..") == 0)
                                continue;
                        if (strlen(dir)+strlen(direntbuf->d_name)+2 > sizeof(name)){
                                fprintf(stderr,"dirwalk : name %s/%s too long\n",dir,direntbuf->d_name);
                                return;
                        }
                        else {
                                sprintf(name,"%s/%s",dir,direntbuf->d_name);
                                (*fcn)(name);
                        }
                }
                printf("--------\n");
        }
        closedir(dirp);
}
void fsize(char *name){
        struct stat stbuf;
        if (stat(name ,&stbuf) == -1){
                fprintf(stderr,"can't access %s\n",name);
                return;
        }
        else{
                if ((stbuf.st_mode & S_IFMT) == S_IFDIR){
                        printf("%s\n",name);
                        dirwalk(name, fsize);
                }
                else{
                        printf("%s\n",name);
                }
        }
        
}



int main(int argc, char **argv){
        char *wd;
        wd = getcwd(NULL,0);
        if (argc == 1){
                fsize(wd);
        }
        else{
                while(--argc > 0){
                        fsize(*++argv);
                }
        }
        free(wd);
        return 0;

}
