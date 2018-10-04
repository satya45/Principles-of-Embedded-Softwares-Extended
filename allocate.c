/**
* @brief  Allocates a memory block
*function allocate which uses malloc to allocate a memory in a pointer.
*
* @author Satya Mehta and Siddhant Jajoo
*/



#include <stdio.h>
#include <stdlib.h>
#include "allocate.h"
#include "dispmem.h"
#include "free.h"



char *p_tr;

void allocate()
{
printf("Enter number of 32 bit words\n");
scanf ("%d", &max_word);
i=4*max_word;
ptr= malloc(i);

last_ptr=ptr + max_word;

if (ptr==NULL)
{
printf("\nCan't allocate memory\n");
exit(0);	
}
printf("\n Memory Allocated and starting memory is %p\n", ptr);


}

	
