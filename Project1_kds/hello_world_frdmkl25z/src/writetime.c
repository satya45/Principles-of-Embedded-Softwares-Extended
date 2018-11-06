#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "writetime.h"
#include "allocate.h"
#include "specifymem.h"
#include "core_cm0plus.h"
#include "main.h"
#include "timer.h"

#ifdef TIME_H
#include <time.h>
#endif

void writetime()
{

__uint32_t word;
one_time=0;
__uint32_t ran_number = 232;


specifymem();

if (n)
	{
		n=0;
		return;
	}



PRINTF("\nEnter the number of words\n");
SCANF("%d", &word);

if (word> (last_ptr-ptr))
		{
			PRINTF("\r\nYou are trying to write the number of words that exceed the allotted words \r\n");
			return;
		}

for (int j=0;j<word;j++)
{

if (one_time==0)
{
PRINTF("\r\nEnter the seed value\r\n");
SCANF("%d", &seed);
one_time++;
}

#ifdef TIME_H
clock_t start = clock();
#else
startVal = SysTick -> VAL;
#endif

__uint32_t Q = prime / seed;
__uint32_t R=  prime % seed;

ran_number = (seed * (ran_number % Q)) - (R * floor(ran_number/Q));

if (ran_number<0) 
{
ran_number = ran_number + prime;
}

ran_number = (ran_number * seed) % prime; 

(new_ptr)=(new_ptr) + (j*1);
(*new_ptr)=ran_number;

PRINTF("\r\n%x:\t%d\r\n",new_ptr,(*new_ptr));

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


