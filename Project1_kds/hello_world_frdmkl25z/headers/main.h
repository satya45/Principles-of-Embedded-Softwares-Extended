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
* @brief Function declarations and global variables declaration
* @author Satya Mehta, Siddhant Jajoo
* @date October 3 2018
* @version 1.0
*
*/


#ifndef MAIN_H
#define MAIN_H main.h


#include <stdio.h>
#include "board.h"
#include "fsl_lptmr_driver.h"
#include "fsl_debug_console.h"
typedef struct
{
char *cmd;
void (*myfunct)();

}table;
 

void ex(void);
__uint32_t e =1;
__uint32_t a =0;
int one_time;
int one_time1;


#endif
