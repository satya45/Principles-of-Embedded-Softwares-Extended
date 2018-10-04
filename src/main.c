#include <stdio.h>
#include <string.h>
#include "../inc/help.h"
#include "../inc/main.h"
#include "../inc/allocate.h"
#include "../inc/dispmem.h"
#include "../inc/free.h"
#include "../inc/write.h"
#include "../inc/writetime.h"
#include "../inc/inverttime.h"
#include "../inc/verifytime.h"


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
