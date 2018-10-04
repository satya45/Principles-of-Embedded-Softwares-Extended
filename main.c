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


char input[20];
int one_time=0;
int one_time1=0;
__uint32_t prime=104473;	
table lookup[]=
{

{"help\n",&h},
{"allocate\n",&allocate},
{"free\n",&fr},
{"dispmem\n",&dispmem},
{"write\n", &write},
{"writetime\n",&writetime},
{"inverttime\n",&inverttime},
{"verifytime\n",&verifytime},
{"ex\n",&ex}
};

void ex(void)
{
e=0;
}



void main()
{

printf("\nType help to invoke Help function\n");

while(e)
{
fgets(input,20,stdin);


for (int i=0; i<sizeof(lookup)/sizeof(lookup[0]); i++)
{ 
	if (strcmp(input,lookup[i].cmd )==0)
	{

		(*lookup[i].myfunct)();
		

	}

}
}
}
