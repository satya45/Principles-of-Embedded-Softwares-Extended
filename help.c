/**
* @brief  Allocates a memory block
*invokes a help function which display's all the available commands
*
* @author Satya Mehta and Siddhant Jajoo
*/


#include<stdio.h>
#include"help.h"

void h()
{

printf("\nYou have entered the help function!\n");
printf("\nType in the following Commands for different functionalities. \n");
printf("\nallocate - This command allocates memory. \n");
printf("\nfree - To free the previous allocated block \n");
printf("\ndispmem - Displays the contents of memory in unsigned 32-bit hexadecimal format\n");
printf("\nwrite - Writes a hexadecimal value provided by the user at the specified location  \n");
printf("\ninverttime - Reports the amount of time to invert all the bits at the specified area of memory. \n");
printf("\nwritetime - Generates a random number and stores it in the memory location specified by the user and returns the amount of time taken to complete the task.\n");
printf("\nverifytime - Verifies the random number generated in a specific memory location and returns the amount of time taken to complete the task. \n");
printf("\n \n"); 

}



