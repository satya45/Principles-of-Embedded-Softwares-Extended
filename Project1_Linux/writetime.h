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
* @brief Writes a psuedo random pattern in a user specified memory using a seed value.
* @author Satya Mehta, Siddhant Jajoo
* @date October 3 2018
* @version 1.0
*
*/



#ifndef WRITETIME_H
#define WRITETIME_H writetime.h

#include <stdio.h>
#include <time.h>

__uint32_t prime;
__uint32_t ran_number;
__uint32_t seed;
int one_time; 

void writetime(void);

#endif
