#include "MKL25Z4.h"
#include <stdio.h>
#include <stdarg.h>
#include "circbuff.h"
#include "main.h"


uint16_t number;
uint16_t divisor_check;
uint16_t divisor;
int8_t power;
uint8_t send_count;

circbuff *SMA;

void uart_init();
void uart_tx(int8_t data);
int8_t uart_rx();
void myscanf(char *str,...);
void myprintf(char * str,...);
