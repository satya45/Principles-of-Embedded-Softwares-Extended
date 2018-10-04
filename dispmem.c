/**
* @brief  Display a memory block
*function calling will ask user to enter a memory or a offset.
*user can enter data into a memory block assigned
* @author Satya Mehta and Siddhant Jajoo
*/


#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "allocate.h"
#include "dispmem.h"
#include "write.h"



int k;

/*memory display function*/


void dispmem()

{	

__uint32_t o=0;
__uint32_t *new_ptr;
char mem[64];
char m;

/*Taking input from user*/
printf("Press M to specify memory location or N to specify offset\n");
again:
scanf(" %c", &m);

if (m=='M')
{
/*Take memory address input*/
printf("\n Enter the memory location address of 12 digits\n");
scanf(" %s", mem);
long input_memloc =strtol(mem, NULL, 16);	
new_ptr= (__uint32_t*)input_memloc;

/*check memory address specified by memory*/
if (strlen(mem)!=12)
{
printf("\nInvalid Memory Location\n");
printf("\nPress M to specify memory location or N to specify offset again\n");

goto again;
}
/*Display memory*/
printf("%p\n",new_ptr);
	
	printf("\nThe memory address content to be displayed is in %p\n",new_ptr);
	printf("\nThe memory address content is :%x\n",*(ptr+o));
	
}
/*if offset specified*/
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
	printf("\nThe memory address content to be displayed is in %p\n",new_ptr);
	printf("\nThe memory address content is :%x\n",*(ptr+o));
	}
	}

	
else if (ptr==NULL)
		{
		printf("Nothing to display\n");

		}



else 
printf("\nwrong command\n");

return;

}
