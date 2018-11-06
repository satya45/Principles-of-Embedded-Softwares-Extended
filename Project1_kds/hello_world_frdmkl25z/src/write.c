#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "allocate.h" 
#include "write.h"
#include "specifymem.h"


void write()
{
__uint32_t word;
char input_data[32];

	specifymem();
	if (n)
	{
		n=0;
		return;
	}
	PRINTF("\r\nEnter the number of words to be written\r\n");
	SCANF("%d", &word);

	if (word > (last_ptr-ptr))
		{
			PRINTF("\r\nYou are trying to write the number of words that exceed the allotted words \r\n");
			return;
		}
	for (int j=0;j<word;j++)
	{

	PRINTF("\r\nEnter the input data\r");
	SCANF("%s",input_data);
	long num =strtol(input_data, NULL, 16);
	(new_ptr)=(new_ptr) + (j*1);
	*new_ptr= (__uint32_t)num;
	PRINTF("\r\nThe data assigned to the memory address %x is %x\r\n",new_ptr, *new_ptr);
	
}	
}

