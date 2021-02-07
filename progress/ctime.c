/* 距离1970.1.1的秒数，把得到的秒数转换成当前时间*/
#include <stdio.h>
#include <time.h>
int main(void)
{
        char buf[1024];
        time_t t;
        time(&t);
        ctime_r(&t, buf);
        printf("%s\n", buf);
        return 0;
}
