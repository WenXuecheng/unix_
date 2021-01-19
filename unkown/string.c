#include<stdio.h>
 
 
int main()
 
{
 
 
char a[][3]={"tr","mi","so"};
char *p = a; 
char (*t)[3] =a ;
 
printf("%s ",a);
printf("%s ",a[1]);
 
 
}


