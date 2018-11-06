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
PRINTF("\r\nEnter number of 32 bit words\r\n");
SCANF("%d", &max_word);
PRINTF("\r\n%d", max_word);
i=4*max_word;

ptr= (uint32_t *)malloc(i);

last_ptr=ptr + max_word;

if (ptr==NULL)
{
PRINTF("\nCan't allocate memory\n");
exit(0);	
}
PRINTF("\r\n Memory Allocated and starting memory is \r\n%x", ptr);

}

	
