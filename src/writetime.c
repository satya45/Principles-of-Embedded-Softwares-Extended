#include <stdio.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include "../inc/writetime.h"
#include "../inc/allocate.h"
#include "../inc/specifymem.h"


	
void writetime()
{
__uint32_t word;
char input_data[32];
one_time=0;
__uint32_t ran_number = 232;


clock_t start = clock();

specifymem();



printf("\nEnter the number of words\n");
scanf("%d", &word);

for (int j=0;j<word;j++)
{

if (one_time==0)
{
printf("\nEnter the seed value\n");
scanf("%d", &seed);
one_time++;
}

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

printf("\n%p:\t%d\n",new_ptr,(*new_ptr));

}
clock_t stop = clock();

double time_taken = ((double)stop - (double)start)/CLOCKS_PER_SEC;

printf("\nTime taken to execute the command is %f\n", time_taken);
}

