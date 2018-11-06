/*****************************************************************************
* Copyright (C) 2018 by Satya Mehta and Siddhant Jajoo
*
* Redistribution, modification or use of this software in source or binary
* forms is permitted as long as the files maintain this copyright. Users are
* permitted to modify this and use it to learn about the field of embedded
* software. Satya Mehta, Siddhant Jajoo and the University of Colorado are not liable for
* any misuse of this material.
*
*****************************************************************************/
/**
* @file allocate.h
* @brief An abstraction for memory read and write operations
*
* This header file provides an abstraction of allocating the memory.
*
* @author Satya Mehta, Siddhant Jajoo
* @date October 3 2018
* @version 1.0
*
*/

//#define TIMER_H

#ifndef ALLOCATE_H
#define ALLOCATE_H allocate.h


#include <stdio.h>
#include "board.h"
#include "fsl_lptmr_driver.h"
#include "fsl_debug_console.h"

uint32_t *ptr;
uint32_t *last_ptr;

__uint32_t n=0;
int i;
int max_word;
void allocate(void);
__uint32_t prime=104473;
#endif
