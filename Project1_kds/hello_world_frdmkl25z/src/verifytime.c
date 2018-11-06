#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "verifytime.h"
#include "writetime.h"
#include "allocate.h"
#include "specifymem.h"
#include "timer.h"

#ifdef TIME_H
#include <time.h>
#endif

void verifytime()
{
char input_data[32];
__uint32_t word;
one_time1=0;
__uint32_t ran_number1 = 232;


specifymem();
if (n)
	{
		n=0;
		return;
	}



PRINTF("\r\nEnter the number of words\r\n");
SCANF("%d", &word);

if (word> (last_ptr-ptr))
		{
			PRINTF("\r\nYou are trying to verify the number of words that exceed the allotted words \r\n");
			return;
		}

#ifdef TIME_H
clock_t start = clock();
#else
startVal = SysTick -> VAL;
#endif

for (int j=0;j<word;j++)
{

if (one_time1==0)
{
PRINTF("\r\nEnter the seed value\r\n");
SCANF("%d", &seed1);
one_time1++;
}

__uint32_t Q = prime / seed1;

__uint32_t R=  prime % seed1;

ran_number1 = (seed1 * (ran_number1 % Q)) - (R * floor(ran_number1/Q));

if (ran_number1<0) 
{
ran_number1 = ran_number1 + prime;
}

ran_number1 = (ran_number1 * seed1) % prime; 


(new_ptr)=(new_ptr) + (j*1);
 
if (*new_ptr==ran_number1)
{
PRINTF("\r\nThe memory address %x has been verified and contains the following value:%d\r\n",new_ptr, *new_ptr);
}

else
{
PRINTF ("\r\nMemory Address:%x\r\n",new_ptr);
PRINTF ("\r\nExpected:\t%d\r\n",(*new_ptr));
PRINTF ("\r\nActual:\t%d\r\n",ran_number1);
}

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


