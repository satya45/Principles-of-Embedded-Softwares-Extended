/*
 * lptmr.h
 *
 *  Created on: Nov 6, 2018
 *      Author: user1
 */

#ifndef LPTMR_H_
#define LPTMR_H_


////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////
// Timer period: 500000uS
#define TMR_PERIOD         500000U
#if defined(TWR_KV46F150M)
#define LPTMR0_IDX LPTMR_IDX
#endif

void lptmr_call_back(void);
void lptmr_config(void);

#endif /* LPTMR_H_ */
