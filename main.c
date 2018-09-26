
#include <stdio.h>
#include "help.h"

void func(void);

void main()
{

printf("Welcome to Sprint");
printf("\nTo invoke help press h");

static void (*help1[])(void)= {help};
while(1)
{
char a;
char b='b';
scanf("%c", &a);
int i;
if (a=='h')
{
i=0;
help1[i]();
a=b;
printf("\nPress Ctrl+C to exit");


}

}

}
