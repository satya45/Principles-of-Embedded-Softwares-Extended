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
hardware_init();
PRINTF("\r\nYou have entered the help function!\r\n");
PRINTF("\r\nType in the following Commands for different functionalities.\r\n");
PRINTF("\r\nallocate - This command allocates memory.\r\n");
PRINTF("\r\nfree - To free the previous allocated block\r\n");
PRINTF("\r\ndispmem - Displays the contents of memory in unsigned 32-bit hexadecimal format\r\n");
PRINTF("\r\nwrite - Writes a hexadecimal value provided by the user at the specified location\r\n");
PRINTF("\r\ninverttime - Reports the amount of time to invert all the bits at the specified area of memory.\r\n");
PRINTF("\r\nwritetime - Generates a random number and stores it in the memory location specified by the user and returns the amount of time taken to complete the task.\r\n");
PRINTF("\r\nverifytime - Verifies the random number generated in a specific memory location and returns the amount of time taken to complete the task.\r\n");
PRINTF("\r\n \r\n");

}



