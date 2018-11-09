/*
 * lptmr.c
 *
 *  Created on: Nov 6, 2018
 *      Author: user1
 */


#include "lptmr.h"
#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "fsl_lptmr_driver.h"
#include "fsl_debug_console.h"
/*!
 * @brief LPTMR interrupt call back function.
 * The function is used to toggle LED1.
*/

void lptmr_call_back(void)
{
    // Toggle LED1
    LED1_TOGGLE;
}


void lptmr_config(void)
{
	// LPTMR configurations
	lptmr_user_config_t lptmrConfig =
	{
			.timerMode = kLptmrTimerModeTimeCounter,
			.freeRunningEnable = false,
			.prescalerEnable = true,
			.prescalerClockSource = kClockLptmrSrcLpoClk,
			.prescalerValue = kLptmrPrescalerDivide2,
			.isInterruptEnabled = false,
	};
	// LPTMR driver state information
	lptmr_state_t lptmrState;

	// Initialize standard SDK demo application pins
	hardware_init();

	// Initialize LPTMR
//	LPTMR_DRV_Init(LPTMR0_IDX, &lptmrState, &lptmrConfig);
	// Set timer period for TMR_PERIOD seconds
	//LPTMR_DRV_SetTimerPeriodUs(LPTMR0_IDX, TMR_PERIOD);
	// Install interrupt call back function for LPTMR
	//LPTMR_DRV_InstallCallback(LPTMR0_IDX, lptmr_call_back);
	// Start LPTMR
//	LPTMR_DRV_Start(LPTMR0_IDX);
}
