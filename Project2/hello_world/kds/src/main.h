/*
 * main.h
 *
 *  Created on: Nov 6, 2018
 *      Author: user1
 */

#ifndef MAIN_H_
#define MAIN_H_

#include <stdint.h>

#define KDS			// Comment this to run this code on linux Platform
#define ELEMENTS		(2)

#ifdef KDS
#define printf PRINTF
#endif

typedef struct
{
	int8_t char_ascii_value;
	uint16_t char_count;
}table;



// RX buffers
//! @param receiveBuff Buffer used to hold received data
uint8_t receiveBuff;
int8_t cb[ELEMENTS];

volatile uint16_t count;
//void disp_count(void);

#endif /* MAIN_H_ */
