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
//#include "fsl_debug_console.h"
#else
#include <stdio.h>
#endif


////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

void calc_prime(void);

void calc_prime(void)
{
	int i, number, ct;
	j=0;
	for(number= 1; number <= total_char; number++)
	{
		ct = 0;
		for (i = 2; i <= number/2; i++)
		{
			if(number%i == 0)
			{
				ct++;
				break;
			}
		}
		if(ct == 0 && number != 1 )
		{
			arr[j] = number;
			j++;
		}
	}
}



// * @brief Main function

int main (void)
{
#ifdef KDS
	// Initialize standard SDK demo application pins
	hardware_init();
#endif
	count = 0;
	resize_flag = 0;
	total_char = 0;
	input_size = 100;
	uart_init();

    LED2_EN;
    SMA = circbuff_init(input_size); //initializing circular buffer

    // Print the initial banner
    myprintf("\r\nHello World!\r\n");

    while(1)
    {
    	calc_prime();

    	if (resize_flag == 1)
    	{
    		resize_buffer();
    		resize_flag = 0;
    		UART0_C2 |= UART0_C2_RIE_MASK;
    	}
    	else if (buffer_size(SMA)!=0)
    	{
    		if (rx_data == 27)
    		{
    			resize_flag = 1;
    			UART0_C2 &=~ UART0_C2_RIE_MASK;
    		}
    		else
    		{
//    			UART0_C2|=UART0_C2_TIE_MASK;
    		}
    	}
    	if (tx_flag == 1)
    	{
    		__disable_irq();
    		tx_flag = 0;
    		__enable_irq();
    		while (buffer_size(SMA)!=0)
    		{
    			total_char++;
    			rx_data = pop(SMA);
    			myprintf("\r\n********************************");
    			myprintf("\r\n=>%c", rx_data);
    			report(rx_data);
    			myprintf(" Prime Numbers till %d: \r\n", total_char);
    			for(int k = 0; k<j; k++)
    			{
    				myprintf(" %d \r\n", arr[k]);
    			}
    		}
    	}
    }
}
