/*
 * circbuff.h
 *
 *  Created on: Nov 6, 2018
 *      Author: user1
 */

#ifndef SRC_CIRCBUFF_H_
#define SRC_CIRCBUFF_H_

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include "main.h"

#ifdef KDS
#include "board.h"
#include "fsl_debug_console.h"
#else
#include <stdio.h>
#endif


typedef struct{

	int8_t *buffer;
	int16_t head;
	int16_t tail;
	int16_t length;
	volatile bool full_status;

}circbuff;



void push(circbuff *circ_b, int8_t data_byte);
int8_t pop(circbuff *circ_b);
void circbuff_reset(circbuff *circ_b);
circbuff *circbuff_init (int16_t length);
void circbuff_free(circbuff *circ_b);
bool buffer_status(circbuff *circ_b);
uint16_t buffer_size(circbuff *circ_b);
void resize_buffer(int8_t data);

#endif /* SRC_CIRCBUFF_H_ */
