#include <stdio.h>
struct msg{
        int numl;
};
int main(void ){

        struct msg *m;
        m = NULL;
        m->numl;
        printf("%d\n",m->numl);
        return 0;
}
