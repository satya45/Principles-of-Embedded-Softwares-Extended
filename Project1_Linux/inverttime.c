/**
* @brief  Inverts data inside a memory 
*User spcifies a location whose data is to be inverted.
*
* @author Satya Mehta and Siddhant Jajoo
*/

#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include "inverttime.h"
#include "writetime.h"
#include "allocate.h"
#include "specifymem.h"

/*Inverttime function*/

void inverttime()
{

__uint32_t word;
char input_data[32];

clock_t start = clock();
specifymem(); //user specifies a memory

printf("\nEnter the number of words to be inverted\n");
scanf("%d", &word);

for (int j=0;j<word;j++)
{
(new_ptr)=(new_ptr) + (j*1);
(*new_ptr) = (*new_ptr) ^ (invert); //inverting data


//(*new_ptr)=ran_number;

printf("\nThe inverted Value of the accessed memory location %p is %x\n",new_ptr, *new_ptr);
}
clock_t stop = clock();

double time_taken = ((double)stop-(double)start)/CLOCKS_PER_SEC;
printf("\nTime taken to execute the command is %f\n", time_taken);

}
