#include "adc.h"
#include <stdint.h>
#include "board.h"


/*adc_init function Initializes ADC*/


int32_t adc_init(void)
{
	/*Enable ADC Clock gates*/
	SIM_SCGC6 |= SIM_SCGC6_ADC0_MASK;
	SIM_CLKDIV1 |= SIM_CLKDIV1_OUTDIV4(2); //Bus clock divide by 8

	if(adc_calib()==-1)
	{
		return -1;
	}
	/*Configuration of ADC*/
	ADC0_CFG1=0;
	ADC0_SC3=0;
	ADC0_CFG1 |= ADC_CFG1_MODE(3) | ADC_CFG1_ADICLK(0) | ADC_CFG1_ADIV(3) | ADC_CFG1_ADLSMP(1);
	ADC0_SC1A |= ADC_SC1_DIFF_MASK| ADC_SC1_AIEN(0);
	ADC0_SC3 |= ADC_SC3_ADCO(1) | ADC_SC3_AVGE(1) | ADC_SC3_AVGS(3);
	ADC0_SC2 |= ADC_SC2_DMAEN_MASK;    // DMA Enable
	ADC0_SC1A &= ~ADC_SC1_ADCH_MASK;

	return 0;
}



uint16_t adc_read(uint8_t ch)

{
	ADC0_SC1A = ch & ADC_SC1_ADCH_MASK; //Write to SC1A to start conversion
	while(ADC0_SC2 & ADC_SC2_ADACT_MASK); 	 // Conversion in progress
	while(!(ADC0_SC1A & ADC_SC1_COCO_MASK)); // Run until the conversion is complete
	return ADC0_RA;
}



int8_t adc_calib(void)
{

		uint16_t calib = 0; // calibration variable

		ADC0_CFG1 |= ADC_CFG1_MODE(3) | ADC_CFG1_ADICLK(1) | ADC_CFG1_ADIV(3); //16bit single ended mode, bus_clk/2, clk divide by 8
		ADC0_SC3 |= ADC_SC3_AVGE_SHIFT | ADC_SC3_AVGS(3) | ADC_SC3_CAL_MASK; //HW avg enable, 32 sample avg, calibration enable

		while(ADC0_SC3 & ADC_SC3_CAL_MASK); // Wait for calibration to end

		if(ADC0_SC3 & ADC_SC3_CALF_MASK)	// Check for successful calibration
		{
			return -1;
		}

		calib += ADC0_CLPS + ADC0_CLP4 + ADC0_CLP3 + ADC0_CLP2 + ADC0_CLP1 + ADC0_CLP0;
		calib /= 2;
		calib |= 0x8000; 	// Set MSB
		ADC0_PG = calib;

		calib = 0;
		calib += ADC0_CLMS + ADC0_CLM4 + ADC0_CLM3 + ADC0_CLM2 + ADC0_CLM1 + ADC0_CLM0;
		calib /= 2;
		calib |= 0x8000;	// Set MSB
		ADC0_MG = calib;

		return 0;
}

