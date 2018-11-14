/*
 * Copyright (c) 2013 - 2014, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

///////////////////////////////////////////////////////////////////////////////
//  Includes
///////////////////////////////////////////////////////////////////////////////
// SDK Included Files

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "main.h"
#include "circbuff.h"
#include "uart.h"


#ifdef KDS
#include "board.h"
#include "fsl_debug_console.h"
#else
#include <stdio.h>
#endif


////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

//Lookup table for counting Characters input
	static table lookup[]=
				 {
						 {0,0}, {1,0},{2,0},{3,0},{4,0},{5,0},{6,0},{7,0},{8,0},{9,0},{10,0},
						 {11,0},{12,0},{13,0},{14,0},{15,0},{16,0},{17,0},{18,0},{19,0},{20,0},
						 {21,0},{22,0},{23,0},{24,0},{25,0},{26,0},{27,0},{28,0},{29,0},{30,0},
						 {31,0},{32,0},{33,0},{34,0},{35,0},{36,0},{37,0},{38,0},{39,0},{40,0},
						 {41,0},{42,0},{43,0},{44,0},{45,0},{46,0},{47,0},{48,0},{49,0},{50,0},
						 {51,0},{52,0},{53,0},{54,0},{55,0},{56,0},{57,0},{58,0},{59,0},{60,0},
						 {61,0},{62,0},{63,0},{64,0},{65,0},{66,0},{67,0},{68,0},{69,0},{70,0},
						 {71,0},{72,0},{73,0},{74,0},{75,0},{76,0},{77,0},{78,0},{79,0},{80,0},
						 {81,0},{82,0},{83,0},{84,0},{85,0},{86,0},{87,0},{88,0},{89,0},{90,0},
						 {91,0},{92,0},{93,0},{94,0},{95,0},{96,0},{97,0},{98,0},{99,0},{100,0},
						 {101,0},{102,0},{103,0},{104,0},{105,0},{106,0},{107,0},{108,0},{109,0},{110,0},
						 {111,0},{112,0},{113,0},{114,0},{115,0},{116,0},{117,0},{118,0},{119,0},{120,0},
						 {121,0},{122,0},{123,0},{124,0},{125,0},{126,0},{127,0},{128,0},{129,0},{130,0},
						 {131,0},{132,0},{133,0},{134,0},{135,0},{136,0},{137,0},{138,0},{139,0},{140,0},
						 {141,0},{142,0},{143,0},{144,0},{145,0},{146,0},{147,0},{148,0},{149,0},{150,0},
						 {151,0},{152,0},{153,0},{154,0},{155,0},{156,0},{157,0},{158,0},{159,0},{160,0},
						 {161,0},{162,0},{163,0},{164,0},{165,0},{166,0},{167,0},{168,0},{169,0},{170,0},
						 {171,0},{172,0},{173,0},{174,0},{175,0},{176,0},{177,0},{178,0},{179,0},{180,0},
						 {181,0},{182,0},{183,0},{184,0},{185,0},{186,0},{187,0},{188,0},{189,0},{190,0},
						 {191,0},{192,0},{193,0},{194,0},{195,0},{196,0},{197,0},{198,0},{199,0},{200,0},
						 {201,0},{202,0},{203,0},{204,0},{205,0},{206,0},{207,0},{208,0},{209,0},{210,0},
						 {211,0},{212,0},{213,0},{214,0},{215,0},{216,0},{217,0},{218,0},{219,0},{220,0},
						 {221,0},{222,0},{223,0},{224,0},{225,0},{226,0},{227,0},{228,0},{229,0},{230,0},
						 {231,0},{232,0},{233,0},{234,0},{235,0},{236,0},{237,0},{238,0},{239,0},{240,0},
						 {241,0},{242,0},{243,0},{244,0},{245,0},{246,0},{247,0},{248,0},{249,0},{250,0},
						 {251,0},{252,0},{253,0},{254,0},{255,0}
				 };
/*
void disp_count()
{
	uint16_t number = lookup[i].char_count;
	uint16_t divisor_check = number;
	uint16_t divisor = 0;
	int8_t power = -1;
	uint8_t send_count = 0;

	while (divisor_check!=0)
	{
		divisor_check = divisor_check/10;
		power++;
	}

	divisor = pow(10,power);

	while (number!=0)
	{
		send_count = number/divisor;
		number = number - send_count*divisor;
		divisor = divisor/10;
		// Convert to ASCII value
		send_count = send_count + 48;
		uart_tx(send_count);
		// printf("%d\r\n",send_count);
	}
}
*/
// * @brief Main function

int main (void)
{
#ifdef KDS
	// Initialize standard SDK demo application pins
	hardware_init();
#endif
	count = 0;
	uart_init();
    // Print the initial banner
    printf("\r\nHello World!\r\n\r\n");

    circbuff *SMA = circbuff_init(ELEMENTS);

    printf("Size of Structure : %d\r\n", sizeof(circbuff));
    printf("Starting Memory Address : %x\r\n", SMA);
    printf("Starting Buffer Memory Address : %x\r\n", SMA->buffer);
    printf("Length : %d\r\n", SMA->length);
    printf("Head : %d\r\n", SMA->head);
    printf("Tail : %d\r\n", SMA->tail);
    printf("Full Status : %d\r\n", SMA->full_status);

    push(SMA,1);
    push(SMA,2);
    push(SMA,3);

    printf("******************************\r\n");

    pop(SMA);
    pop(SMA);
    pop(SMA);

    push(SMA,10);
    circbuff_free(SMA);
    (lookup[65].char_count)++;

    for (uint8_t i=66;i<68;i++)
    {
    	printf("%c = %d\r\n",lookup[i].char_ascii_value,lookup[i].char_count);
    }

    printf("%c and %d\r\n" , lookup[65].char_ascii_value,lookup[65].char_ascii_value);
    printf("%c and %d\r\n" , lookup[66].char_ascii_value,lookup[66].char_ascii_value);


    while(1)
    {


    	int8_t a = uart_rx();

    	uart_tx(a);
    	//uart_tx(13);

    	for (int i=0; i<sizeof(lookup)/sizeof(lookup[0]); i++)
    	{
    		if (a==lookup[i].char_ascii_value)
    		{
//    			printf("\r\n%c\r\n",i);
//    			printf("\r\n%d\r\n",i);

    			(lookup[i].char_count) = 234;

//    			printf("%d",lookup[i].char_ascii_value);
//    			printf("%d",lookup[i].char_count);

    			//********************************************************//
    			uint16_t number = lookup[i].char_count;
    			uint16_t divisor_check = number;
    			uint16_t divisor = 0;
    			int8_t power = -1;
    			uint8_t send_count = 0;

    			while (divisor_check!=0)
    			{
    				divisor_check = divisor_check/10;
    				power++;
    			}

    			divisor = pow(10,power);

    			while (number!=0)
    			{
    				send_count = number/divisor;
    				number = number - send_count*divisor;
    				divisor = divisor/10;
    				// Convert to ASCII value
    				send_count = send_count + 48;
    				uart_tx(send_count);
    				// printf("%d\r\n",send_count);
    			}
    		}
    	}


        // Main routine that simply echoes received characters forever

        // First, get character
//#ifdef KDS
//    	receiveBuff = GETCHAR();
//
//        // Now echo the received character
//        PUTCHAR(receiveBuff);
//#endif
    }
}

