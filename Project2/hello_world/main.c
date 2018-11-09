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

#include "main.h"
#include "circbuff.h"


#ifdef KDS
#include "board.h"
#include "fsl_lptmr_driver.h"
#include "fsl_debug_console.h"
#include "lptmr.h"
#endif


////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////
// Timer period: 500000uS
//#define TMR_PERIOD         500000U
//#if defined(TWR_KV46F150M)
//#define LPTMR0_IDX LPTMR_IDX
//#endif

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////


// * @brief Main function

int main (void)
{
	// Initialize standard SDK demo application pins
	//hardware_init();

	count = 0;

	/*Configure lptmr*/
    lptmr_config();

    // Initialize LED1
    LED1_EN;

    // Print the initial banner
    printf("\r\nHello World!\r\n\r\n");

    circbuff *SMA = circbuff_init(elements);

    printf("Size of Structure %d\r\n", sizeof(circbuff));
    printf("Starting Memory Address %x\r\n", SMA);

    printf("Starting Buffer Memory Address %x\r\n", SMA->buffer);
    printf("Length %d\r\n", SMA->length);
    printf("Head %d\r\n", SMA->head);
    printf("Tail %d\r\n", SMA->tail);
    printf("Full Status %d\r\n", SMA->full_status);
    printf("Data %d\r\n", SMA->data);


    push(SMA,1);
    push(SMA,2);

    printf("******************************");

    pop(SMA);
    pop(SMA);

    //circbuff_free(SMA);

    /*
    buffinit(my_circ_buff, 32);
	int in_data=23;

	if (push(&my_circ_buff, in_data))
	{
		printf("Out of space in CB\r\n");
	}
	circbuff *i= &my_circ_buff;
	printf("Push:%d\r\n", in_data);
	printf("Data in First Loacation=%d\r\n", i->buffer[0]);
    */
    while(1)
    {
        // Main routine that simply echoes received characters forever

        // First, get character
        receiveBuff = GETCHAR();

        // Now echo the received character
        PUTCHAR(receiveBuff);
    }
}

