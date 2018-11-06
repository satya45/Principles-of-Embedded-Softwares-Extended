#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include "specifymem.h"
#include "allocate.h"


void specifymem()
{

if (ptr != NULL)
{

char mem[13];
char m;
__uint32_t o;


PRINTF("\r\nPress M to specify memory location or N to specify offset\r\n");
again:
SCANF("%c", &m);
if (m=='M')
{
PRINTF("\r\n Enter the memory location address of 4 digits\r\n");
SCANF(" %s", mem);

if (strlen(mem)!=4)
{
PRINTF("\r\nInvalid Memory Location\r\n");
PRINTF("\r\nPress M to specify memory location or N to specify offset again\r\n");

goto again;
}

long input_memloc =strtol(mem, NULL, 32);
new_ptr= (__uint32_t*)input_memloc;		

PRINTF("\r\nThe Memory address accessed is:%x\r\n",new_ptr);
	
}
else if (m=='N')	
{
PRINTF("\r\nEnter the offset\r\n");
SCANF(" %d",&o);


if (o>max_word)
	{
	PRINTF("\r\nInvalid! Your offset cannot be greater than number of words\r\n");
	PRINTF("\r\nPress M to specify memory location or N to specify offset again\r\n");
	goto again;
		
	}
	else
	{	
	(new_ptr)= (ptr) + o;
	PRINTF("\r\nThe Memory address accessed is:%x\r\n",new_ptr);
	}


}
}
	else
	{
		PRINTF("\r\nAllocate Memory first\r\n");
		n=1;
	}
}
