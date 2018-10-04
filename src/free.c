#include <stdio.h>
#include <stdlib.h>
#include "../inc/free.h"
#include "../inc/allocate.h"

void fr()
{

free(ptr);
for(int j=0; j<4; j++)
{
printf("%x\n", *ptr);
}
printf("Memory freed\n");

} 



