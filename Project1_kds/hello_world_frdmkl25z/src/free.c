#include <stdio.h>
#include <stdlib.h>
#include "free.h"
#include "allocate.h"

void fr()
{
free(ptr);
PRINTF("%x\r\n", ptr);
PRINTF("Memory freed\n");
ptr = NULL;

} 



