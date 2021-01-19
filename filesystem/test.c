#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(void)
{
        int fdtty;
        fdtty = open("/dev/tty",O_WRONLY);
        write(fdtty,"here",4);
        close(fdtty);
        return 0;
}
