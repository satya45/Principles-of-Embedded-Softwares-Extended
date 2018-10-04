#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include "../inc/verifytime.h"
#include "../inc/writetime.h"
#include "../inc/allocate.h"
#include "../inc/specifymem.h"

void verifytime()
{
char input_data[32];
__uint32_t word;
one_time1=0;
__uint32_t ran_number1 = 232;

clock_t start = clock();
specifymem();



printf("\nEnter the number of words\n");
scanf("%d", &word);

for (int j=0;j<word;j++)
{

if (one_time1==0)
{
printf("\nEnter the seed value\n");
scanf("%d", &seed1);
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
printf("\nThe memory address %p has been verified and contains the following value:%d \n",new_ptr, *new_ptr);
}

else
{
printf ("\nMemory Address:%p\n",new_ptr);
printf ("\nExpected:\t%d\n",(*new_ptr));
printf ("\nActual:\t%d\n",ran_number1);
}

}

clock_t stop = clock();

double time_taken = ((double)stop - (double)start)/CLOCKS_PER_SEC;

printf("\nTime taken to execute the command is %f\n", time_taken);


}


