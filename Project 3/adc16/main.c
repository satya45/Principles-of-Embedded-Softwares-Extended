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
#include "adc.h"
#include "circbuff.h"
#include "uart.h"
#include "uart.h"
#include <stdio.h>
#include <string.h>
#include "fsl_debug_console.h"
#include "dma.h"
#include "board.h"


uint32_t* buffer_init(void)
{

	int *ptr = malloc(64 * sizeof(int));
	if(ptr == 'NULL')
	{
		return 'NULL';
	}
	return ptr;

}

int main(void)
{
	hardware_init();
	int16_t peak;
	GPIO_TEST_EN;
	buff1= buffer_init();
	if(buff1 == 'NULL')
	{
		PRINTF("Buffer Initialization Failed");
	}
	adc_init();
	dma_init();
	LED2_EN;
	LED1_EN;
	PRINTF("HELLO WORLD\r\n");

	while(1)
	{
		if(flag==1)
		{
			//		peak= value[0];
			//			for(int i=0; i<64; i++)
			//			{
			//				if(peak < value[i])
			//				{
			//					peak = value[i];
			//				}
			//				PRINTF("ADC DATA: %d\r\n", value[i]);
			//			}
//			PRINTF("PEAK VALUE : %d\r\n", peak);
			flag=0;
			DMA_DAR0= (uint32_t)buff1[h1];
			DMA_DSR_BCR0 |= DMA_DSR_BCR_BCR(128);
		}

	}
}



////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
