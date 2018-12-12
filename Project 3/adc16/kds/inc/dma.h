#include "MKL25Z4.h"
#include <stdlib.h>

void dma_init(void);

uint8_t vat[3];
int16_t value[64];
uint32_t addr[64];
uint8_t tmp=0;
int flag;
void dma_init(void);
void DMA0_IRQHandler(void);
