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
#include "specifymem.h"



int k;

void dispmem()

{	
__uint32_t word;

specifymem();

if (n)
	{
		n=0;
		return;
	}

printf ("]r\nEnter the number of words to be displayed\r\n");
scanf ("%d",&word);

if (word>(last_ptr-ptr))
		{
			PRINTF("\r\nYou are trying to write the number of words that exceed the allotted words \r\n");
			return;
		}

for (int j=0;j<word;j++)
	{
		(new_ptr) = (new_ptr) + (j*1);
		printf ("\r\nThe Data assigned to the memory address %x is %x\r\n",new_ptr, *new_ptr);

	}
}
