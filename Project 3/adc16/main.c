/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
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
#include <stdio.h>
#include <string.h>
#include "adc.h"
#include "uart.h"
#include "dma.h"
#include "board.h"
#include "main.h"
//#include "fsl_debug_console.h"


#define DECAY (0.8)

int16_t peak, max_peak=0;


/*Function to calculate Peak and Log Values*/
void log_value(void)
{
	peak = buff1[0];
	for(int x = h1; x < (h1+64); x++)
			{
			myprintf(" ADC DATA: %d\r\n", buff1[x]);

				if( buff1[x] < 0)
				{
					buff1[x] = buff1[x] * (-1);
				}

				if (peak < buff1[x])
				{
					peak = buff1[x];
				}

				/*Uncomment following code to display LOG values of ADC Data*/
				/*
				buff1[x] = buff1[x]/1639;
				for (uint8_t j=0;j<20;j++)
				{
					if (lookup[j].adc_value_q == buff1[x])
					{
//						myprintf(" LOG VALUE:%f\r\n",lookup[j].dbfs);
					}
				}
				 */
			}
	if(peak > max_peak)
	{
		max_peak = peak;
	}
	else
	{
		max_peak = max_peak * DECAY;
	}
	myprintf(" MAX PEAK: %d\r\n", max_peak);
	max_peak = max_peak/1639;
	for (uint8_t j=0;j<20;j++)
	{
		if (lookup[j].adc_value_q == max_peak)
		{
			myprintf(" LOG VALUE:%f\r\n",lookup[j].dbfs);
		}
	}

	myprintf("******************************************\r\n\r\n");
}




int main(void)
{
	hardware_init();
	uart_init();
	GPIO_TEST_EN;
	adc_init();
	dma_init();
	LED2_EN;
	LED1_EN;
	myprintf(" HELLO WORLD\r\n");

	while(1)
	{
		//check DMA flag if raised
	if (dma_flag)
		{
			log_value();
			dma_flag=0;
		}
	}
}







////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
