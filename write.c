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

	printf("\nEnter the number of words to be written\n");
	scanf("%d", &word);

	for (int j=0;j<word;j++)
	{

	printf("Enter the input data\n");
	scanf(" %s",input_data);
	long num =strtol(input_data, NULL, 16);
	(new_ptr)=(new_ptr) + (j*1);
	*new_ptr= (__uint32_t)num;
	printf("\nThe data assigned to the memory address %p is %x\n",new_ptr, *new_ptr);
	
}	
}

