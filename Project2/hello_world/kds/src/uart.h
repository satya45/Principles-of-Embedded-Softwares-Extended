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
int8_t resize_flag;
circbuff *SMA;
circbuff *TMA;

volatile int8_t rx_data;
volatile int8_t x;
uint8_t p_flag;
uint8_t s_flag;
volatile int8_t data;

void uart_init();
void bufferload(void);
void uart_tx(int8_t data);
int8_t uart_rx();
void myscanf(char *,...);
void myprintf(char *,...);
void report(int8_t);
void uart_tx_irq(int8_t data);

