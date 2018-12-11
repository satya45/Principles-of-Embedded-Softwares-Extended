#include "MKL25Z4.h"
#include <stdlib.h>

void dma_init(void);

int32_t value[64];
int32_t addr[64];
int flag =0;
int tmp=0;
void dma_init(void);
void DMA0_IRQHandler(void);
