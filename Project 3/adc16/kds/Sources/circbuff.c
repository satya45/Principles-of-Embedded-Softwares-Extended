/*
 * circbuff.c
 *
 *  Created on: Nov 6, 2018
 *      Author: user1
 */

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#include "main.h"
#include "circbuff.h"
#include "uart.h"


/*Inserts an element in the Circular buffer*/
void push(circbuff *circ_b, int8_t data_byte)
{
	if (buffer_status(circ_b))
	{
		myprintf("Buffer is Full\r\n");
	}
	else
	{
//		myprintf("Buffer is not full and Element can be inserted\r\n");
	}

	if (count != input_size)
	{
		circ_b->buffer[circ_b->head] = data_byte;
		//		myprintf ("Value inserted at position %d is %d\r\n", circ_b->head, circ_b->buffer[circ_b->head]);
		circ_b->head = (circ_b->head + 1) % input_size;
		count = (count % input_size) + 1;		//Denotes the number of elements in the Buffer
	}
}

/*Reads the oldest element from the circular buffer*/
int8_t pop(circbuff *circ_b)
{
	if (!buffer_status(circ_b))
	{
//		myprintf("Buffer is Empty\r\n");
	}
	else
	{
//		myprintf("Buffer contains elements and can be read\r\n");
	}

	if (count != 0)
	{
//		myprintf ("Value read at position %d is %d\r\n", circ_b->tail, circ_b->buffer[circ_b->tail]);
		pop_value = circ_b->buffer[circ_b->tail];
		circ_b->tail = (circ_b->tail + 1) % input_size;
		count--;
		return (pop_value);
	}
	return -1;
}

/*Resets the Circular Buffer Parameters*/
void circbuff_reset(circbuff *circ_b)
{
	circ_b->head = 0;
	circ_b->tail =0;
	circ_b->full_status =  false;
}

circbuff * circbuff_init (int16_t length)
{
	my_circ_buff = (circbuff *) malloc(sizeof(circbuff));
	my_circ_buff->buffer = (int16_t *)malloc (length);
	if(my_circ_buff->buffer=='NULL')
	{
		myprintf("Initialization failed\r\n");
//		return
	}
	my_circ_buff->length = length;
	circbuff_reset(my_circ_buff);

	return (my_circ_buff);
}

/*Frees the Memory Allocated*/
void circbuff_free(circbuff *circ_b)
{
	free(circ_b);
	circ_b = NULL;
}

/*Gets the buffer Status if it is Empty or Full*/
bool buffer_status(circbuff *circ_b)
{
	if (count == 0)
	{
		circ_b->full_status = false;
	}

	else if (count == input_size)
	{
		circ_b->full_status = true;
	}

	return (circ_b->full_status);
}

/*Returns the number of elements in the Circular Buffer */
uint16_t buffer_size(circbuff *circ_b)
{
	return(count);
}


void resize_buffer(void)
{
	start:
	myprintf("Enter the New Buffer Size\r\n");
	uint8_t i =0;
	uint8_t z[5] ={0};

	do
	{
		z[i] = uart_rx();
		uart_tx(pop(SMA));
		i++;
	}
	while (z[i-1]!= 13);

	myprintf("Check Values\r\n");
	input_size = atoi(z);
	if (input_size == 0)
	{
		myprintf ("Buffer Size cannot be Zero");
		goto start;
	}
	myprintf("\r\n%d", input_size);
	my_circ_buff->buffer=(int8_t*)realloc(my_circ_buff->buffer, input_size);
	SMA= my_circ_buff;
}

