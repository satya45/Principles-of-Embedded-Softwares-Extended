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


/*Inserts an element in the Circular buffer*/
void push(circbuff *circ_b, int8_t data_byte)
{
	if (buffer_status(circ_b))
	{
		printf("Buffer is Full\r\n");
	}
	else
	{
		printf("Buffer is not full and Element can be inserted\r\n");
	}

	if (count != elements)
	{
		circ_b->buffer[circ_b->head] = data_byte;
		printf ("Value inserted at position %d is %d\r\n", circ_b->head, circ_b->buffer[circ_b->head]);
		circ_b->head = (circ_b->head + 1) % elements;
		count = (count % elements) + 1;		//Denotes the number of elements in the Buffer
		//	count = (count & elements) + 1;
	}
}

/*Reads the oldest element from the circular buffer*/
void pop(circbuff *circ_b)
{
	if (!buffer_status(circ_b))
	{
		printf("Buffer is Empty\r\n");
	}
	else
	{
		printf("Buffer contains elements and can be read\r\n");
	}

	if (count != 0)
	{
		printf ("Value read at position %d is %d\r\n", circ_b->head, circ_b->buffer[circ_b->head]);
		circ_b->tail = (circ_b->tail + 1) % elements;
		count--;
	}
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
//	circbuff * my_circ_buff = (circbuff *) malloc(length + sizeof(circbuff));
	//	my_circ_buff->buffer  = (int8_t *)my_circ_buff + 1 ;
	//	my_circ_buff->buffer  = cb;
	circbuff * my_circ_buff = (circbuff *) malloc(sizeof(circbuff));
	my_circ_buff->buffer = (int8_t *)malloc (length);
	my_circ_buff->length = length;
	circbuff_reset(my_circ_buff);

	return (my_circ_buff);
}

/*Frees the Memory Allocated*/
void circbuff_free(circbuff *circ_b)
{
	free(circ_b);
	circ_b = NULL;
	printf("Starting Memory Address after FREE : %x\r\n", circ_b);
}

/*Gets the buffer Status if it is Empty or Full*/
bool buffer_status(circbuff *circ_b)
{
	if (count == 0)
	{
		circ_b->full_status = false;
	}

	else if (count == elements)
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
