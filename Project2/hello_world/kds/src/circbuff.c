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



void push(circbuff *circ_b, int8_t data_byte)
{
	if (!buffer_status(circ_b))
	{

		circ_b->buffer[circ_b->head] = data_byte;
		printf ("Value at %d place is %d\r\n", circ_b->head, circ_b->buffer[circ_b->head]);
		circ_b->head = (circ_b->head + 1) % elements;
		count = (count % elements) + 1;
		//	count = (count & elements) + 1;
	}
}

void pop(circbuff *circ_b)
{
	if (buffer_status(circ_b))
	{
		printf ("Value at %d place is %d\r\n", circ_b->head, circ_b->buffer[circ_b->head]);
		circ_b->tail = (circ_b->tail + 1) % elements;
		count--;
	}
}

void circbuff_reset(circbuff *circ_b)
{
	circ_b->head = 0;
	circ_b->tail =0;
	circ_b->full_status =  false;
}

circbuff * circbuff_init (int16_t length)
{
//	circbuff * my_circ_buff = (circbuff *) malloc(length + sizeof(circbuff));
	circbuff * my_circ_buff = (circbuff *) malloc(sizeof(circbuff));
	my_circ_buff->buffer = (int8_t *)malloc (length);
	printf("%x\r\n", my_circ_buff);
//	my_circ_buff->buffer  = (int8_t *)my_circ_buff + 1 ;
//	my_circ_buff->buffer  = cb;
	printf("%x\r\n",my_circ_buff->buffer);
	my_circ_buff->length = length;
	circbuff_reset(my_circ_buff);

	return (my_circ_buff);
}

void circbuff_free(circbuff *circ_b)
{
	free(circ_b);
	circ_b = NULL;
}

bool buffer_status(circbuff *circ_b)
{
	if (count >= 0 && count <= elements)
	{
		printf("Buffer is Empty\r\n");
		circ_b->full_status = false;
	}

	else if (count == elements)
	{
		printf("Buffer is full\r\n");
		circ_b->full_status = true;
	}

	return (circ_b->full_status);
}
