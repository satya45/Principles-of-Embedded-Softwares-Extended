#include <stdio.h>
#include <stdlib.h>
#include "../inc/allocate.h"
#include "../inc/dispmem.h"
#include "../inc/free.h"



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

	
