#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "inverttime.h"
#include "writetime.h"
#include "allocate.h"
#include "specifymem.h"
#include "timer.h"

#ifdef TIME_H
#include <time.h>
#endif

void inverttime()
{

__uint32_t word;
char input_data[32];


specifymem();
if (n)
	{
		n=0;
		return;
	}


PRINTF("\r\nEnter the number of words to be inverted\r\n");
SCANF("%d", &word);

if (word> (last_ptr-ptr))
		{
			PRINTF("\r\nYou are trying to invert the number of words that exceed the allotted words \r\n");
			return;
		}

#ifdef TIME_H
clock_t start = clock();
#else
startVal = SysTick -> VAL;
#endif

for (int j=0;j<word;j++)
{
(new_ptr)=(new_ptr) + (j*1);
(*new_ptr) = (*new_ptr) ^ (invert);



PRINTF("\r\nThe inverted Value of the accessed memory location %x is %x\r\n",new_ptr, *new_ptr);
}

#ifdef TIME_H
clock_t stop = clock();
double time_taken = ((double)stop - (double)start)/CLOCKS_PER_SEC;
#else
endVal = SysTick -> VAL;
dif = (double)(startVal - endVal);
dif= (double)(dif/48);
#endif


PRINTF("\r\nTime taken to execute the command is %f us\r\n", dif);
}
