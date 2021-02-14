#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
int main(void )
{
        int i = open("./sc.test",O_RDWR|O_CREAT,0666);
        ftruncate(i,10000000000);
}
