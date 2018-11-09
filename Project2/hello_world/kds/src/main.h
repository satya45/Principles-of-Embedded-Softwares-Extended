/*
 * main.h
 *
 *  Created on: Nov 6, 2018
 *      Author: user1
 */

#ifndef MAIN_H_
#define MAIN_H_

#include <stdint.h>

#define KDS
#define elements		(2)

#ifdef KDS
#define printf PRINTF
#endif

// RX buffers
//! @param receiveBuff Buffer used to hold received data
uint8_t receiveBuff;
int8_t cb[elements];
volatile uint16_t count;

#endif /* MAIN_H_ */
