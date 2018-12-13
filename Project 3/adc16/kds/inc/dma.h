#include "MKL25Z4.h"
#include <stdlib.h>

void dma_init(void);

uint32_t addr[64];
volatile uint8_t dma_flag = 0;
int16_t buff1[128];
uint16_t h1=0;
uint16_t h2=127;


void dma_init(void);
void DMA0_IRQHandler(void);
