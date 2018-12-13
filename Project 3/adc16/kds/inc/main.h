/*
 * main.h
 *
 *  Created on: Nov 6, 2018
 *      Author: user1
 */

#ifndef MAIN_H_
#define MAIN_H_

#include <stdint.h>

#define KDS			// Comment to run on linux Platform
#define ELEMENTS		(10)

#ifdef KDS
#define printf PRINTF
#endif

typedef struct
{
	uint8_t adc_value_q;
	float dbfs;
}table;

table lookup[]=
			 {
					 {0,-26.02}, {1,-20},{2,-16.47},{3,-13.97},{4,-12.14},{5,-10.45},
					 {6,-9.11},{7,-7.95},{8,-6.93},{9,-6.02},{10,-5.19},
					 {11,-4.43}, {12,-3.74},{13,-3.09},{14,-2.49},{15,-1.19},{16,-1.41},
					 {17,-0.91},{18,-0.44},{19,0}
			 };

// RX buffers
//! @param receiveBuff Buffer used to hold received data

volatile uint16_t count;
volatile uint16_t total_char;
uint16_t arr[50];
int j = 0;
uint8_t tx_flag = 0;
uint8_t rx_flag = 0;

#endif /* MAIN_H_ */
