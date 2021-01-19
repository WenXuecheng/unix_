#include <unistd.h> 
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
int main(void) {
        char * a[] = {"ls","-l",NULL,NULL};
execvp(a[0], a);
perror("exec ps");
exit(1);
}
