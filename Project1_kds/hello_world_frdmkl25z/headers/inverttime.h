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
* @brief Header file of inverting a user specified memory 
* @author Satya Mehta, Siddhant Jajoo
* @date October 3 2018
* @version 1.0
*
*/



#ifndef INVERTTIME_H
#define INVERTTIME_H inverttime.h

#define invert 0xFFFFFFFF
#include "board.h"
#include "fsl_lptmr_driver.h"
#include "fsl_debug_console.h"

void inverttime(void);


#endif
