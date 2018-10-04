#include <stdio.h>
#include <stdlib.h>
#include "free.h"
#include "allocate.h"

void fr()
{

free(ptr);
for(int j=0; j<4; j++)
{
printf("%x\n", *ptr);
}
printf("Memory freed\n");

} 



