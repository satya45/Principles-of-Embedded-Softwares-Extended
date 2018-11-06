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
* @brief Header file of verifytime which verifies the psuedo random pattern generated.
* @author Satya Mehta, Siddhant Jajoo
* @date October 3 2018
* @version 1.0
*
*/


#ifndef VERIFYTIME_H
#define VERIFYTIME_H verifytime.h
#include "board.h"
#include "fsl_lptmr_driver.h"
#include "fsl_debug_console.h"

__uint32_t ran_number1;
__uint32_t seed1;
int one_time1; 

void verifytime(void);

#endif 
