#include "board.h"
#include "fsl_lptmr_driver.h"
#include "fsl_debug_console.h"
#include <stdio.h>
#include <string.h>
#include "help.h"
#include "main.h"
#include "allocate.h"
#include "dispmem.h"
#include "free.h"
#include "write.h"
#include "writetime.h"
#include "inverttime.h"
#include "verifytime.h"
#include "timer.h"



char input[20];
one_time=0;
one_time1=0;
table lookup[]=
{

{"help",&h},
{"allocate",&allocate},
{"free",&fr},
{"dispmem",&dispmem},
{"write", &write},
{"writetime",&writetime},
{"inverttime",&inverttime},
{"verifytime",&verifytime},
{"ex",&ex}
};

void ex(void)
{
e=0;
}

void main()
{

hardware_init();
SysTick_config();

LED1_EN;
PRINTF("\r\nType help to invoke Help function\r\n");
LED1_ON;

while(e)
{

SCANF("%s", input);
PRINTF("\r\n%s", input);


for (int i=0; i<sizeof(lookup)/sizeof(lookup[0]); i++)
{
	if (strcmp(input,lookup[i].cmd)==0)
	{
		(*lookup[i].myfunct)();
		a=0;
	}
	else
	{
		a++;
	}
}
if (a>8)
	{
	PRINTF("\r\nInvalid Command\r\n");
	a=0;
	}
}
}
