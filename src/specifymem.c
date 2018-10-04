#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include "../inc/specifymem.h"
#include "../inc/allocate.h"


void specifymem()
{

char mem[13];
char m;
__uint32_t o;


printf("Press M to specify memory location or N to specify offset\n");
again:
scanf(" %c", &m);
if (m=='M')
{
printf("\n Enter the memory location address of 12 digits\n");
scanf(" %s", mem);

if (strlen(mem)!=12)
{
printf("\nInvalid Memory Location\n");
printf("\nPress M to specify memory location or N to specify offset again\n");

goto again;
}

long input_memloc =strtol(mem, NULL, 16);	
new_ptr= (__uint32_t*)input_memloc;		

printf("\nThe Memory address accessed is:%p\n",new_ptr);
	
}
else if (m=='N')	
{
printf("\nEnter the offset\n");
scanf(" %d",&o);


if (o>max_word)
	{
	printf("\nInvalid! Your offset cannot be greater than number of words\n");
	printf("\nPress M to specify memory location or N to specify offset again\n");	
	goto again;
		
	}
	else
	{	
	(new_ptr)= (ptr) + o;
printf("\nThe Memory address accessed is:%p\n",new_ptr);
	}


}


}
