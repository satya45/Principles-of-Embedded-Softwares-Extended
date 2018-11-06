/*
 * time.c
 *
 *  Created on: Nov 1, 2018
 *      Author: satya
 */
#include "timer.h"
#include "MKL25Z4.h"
#include "stdio.h"


void SysTick_config()
{
	SysTick->CTRL  = 0x5;
	SysTick->LOAD |= SysTick_LOAD_RELOAD_Msk;
	SysTick -> VAL = 0;
}
