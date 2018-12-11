#include "dma.h"


void dma_init(void)
{
	/*DMA CLOCK CONFIG*/
	SIM_SCGC6 |= SIM_SCGC6_DMAMUX_MASK;
	SIM_SCGC7 |= SIM_SCGC7_DMA_MASK;

	DMAMUX0_CHCFG0 = 0x00;
	/*Configure Source and Dest*/
	DMA_SAR0= (uint32_t)&ADC0_RA;
	DMA_DAR0= (uint32_t)value;
	DMA_DSR_BCR0 = DMA_DSR_BCR_BCR(4); // 2 bytes (16 bits) per transfer
	DMA_DCR0 |= (DMA_DCR_EINT_MASK | DMA_DCR_ERQ_MASK | DMA_DCR_CS_MASK | DMA_DCR_SSIZE(4)|
	DMA_DCR_DINC_MASK | DMA_DCR_DMOD(5) | DMA_DCR_DSIZE(4));

	// Enable DMA channel and source
	DMAMUX0_CHCFG0 |= DMAMUX_CHCFG_ENBL(1) | DMAMUX_CHCFG_SOURCE(40); // Enable DMA channel and set ADC0 as source
	// Enable interrupt
//	NVIC->ISER[0] |= (uint32_t)(1UL << (((uint32_t)(int32_t)DMA0_IRQn) & 0x1FUL));
	NVIC_EnableIRQ(DMA0_IRQn);

}

void DMA0_IRQHandler(void)
	{

		/* Enable DMA0*/
 		DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE_MASK;	// Clear Done Flag
		DMA_DSR_BCR0 |= DMA_DSR_BCR_BCR(4);		// Set byte count register
		addr[tmp]= DMA_DAR0;
		tmp++;
		if(tmp==64)
		{
		flag=1;
		}

	}





