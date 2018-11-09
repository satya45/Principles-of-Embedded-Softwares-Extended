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

#ifdef KDS
#include "board.h"
#include "fsl_debug_console.h"
#endif


typedef struct{

	int8_t *buffer;
	int8_t data;
	int16_t head;
	int16_t tail;
	int16_t length;
	volatile bool full_status;

}circbuff;


#define buffinit(x,y) int bufflen[y+1];\
		circbuff x= {\
				.buffer=bufflen,\
				.head=0,\
				.tail=0,\
				.length=y+1\
};


void push(circbuff *circ_b, int8_t data_byte);
void pop(circbuff *circ_b);
void circbuff_reset(circbuff *circ_b);
circbuff *circbuff_init (int16_t length);
void circbuff_free(circbuff *circ_b);
bool buffer_status(circbuff *circ_b);

#endif /* SRC_CIRCBUFF_H_ */
