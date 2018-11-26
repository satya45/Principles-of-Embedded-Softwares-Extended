
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include "MKL25Z4.h"
//#include "board.h"
#include "uart.h"
#include "circbuff.h"
#include "main.h"


#define OSR_VAL (16)
#define SYS_CLOCK (48000000)
#define BAUD (115200)


void uart_init()
{

	/*Clock Enable*/
	SIM->SCGC4 |= SIM_SCGC4_UART0_MASK; //turn ON clock gate
	SIM->SOPT2 |= 0x4000000; //FLL or PLL Clock

	/*Enable ALT2 Pins*/
	/*UART RX/TX connected to Port A*/
	UART0_C2 &= ~(UART0_C2_TE_MASK | UART0_C2_RE_MASK);
	UART0->C1 &= ~(UART0_C1_M_MASK | UART0_C1_PE_MASK);
	UART0->BDH &= ~UART_BDH_SBNS(1);


	/*Baud Config*/
	uint16_t SBR=((SystemCoreClock)/(OSR_VAL*BAUD));
	UART0_C4=UART0_C4_OSR(0x0F);
	UART0_BDH= ((SBR>>8)& UART0_BDH_SBR_MASK);
	UART0_BDL=(SBR & UART0_BDL_SBR_MASK);
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK; //enable PORTA
	PORTA_PCR1 = PORT_PCR_MUX(2);
	PORTA_PCR2 = PORT_PCR_MUX(2);

	/*Enable Transmitter, Receiver and Receiver interrupt*/
	UART0_C2 |= (UART0_C2_TE_MASK)|(UART_C2_RE_MASK)|(UART_C2_RIE_MASK); //transmitter enable, Receiver enable
	/*Enable IRQ*/
	__enable_irq();

	NVIC_EnableIRQ(UART0_IRQn);
}


void uart_tx(int8_t data)
{

	while(!(UART0->S1 & UART_S1_TDRE_MASK)); //Waiting for the buffer to get empty
	UART0->D = data;
	while(!(UART0->S1 & UART_S1_TC_MASK)); //Waiting for transmission to get complete

}

int8_t uart_rx()
{
	int8_t data;
	while((UART0->S1 & UART_S1_RDRF_MASK) == 0);
	data = UART0->D;
	push(SMA,data);
	return data;
}

void report(int8_t x)
{
	if(x!= -1)
	{
		for (int i=32; i<128; i++)
		{
			if (x==lookup[i].char_ascii_value)
			{
				(lookup[i].char_count)++;
				myprintf("\r\n*REPORT*\r\n");

				//********************************************************//
				for (int i=32; i<128; i++)
				{
					if (lookup[i].char_count != 0)
					{
						myprintf(" \r\n%c=%d \r\n", lookup[i].char_ascii_value, lookup[i].char_count);
					}
				}
				myprintf("Total Character = %d \r\n", total_char);
			}
		}
	}

}


void UART0_IRQHandler()
{
__disable_irq();

 if (UART0_S1 & UART_S1_RDRF_MASK)
 {
//	 myprintf("Printing..");
	 rx_data=UART0->D;
	 if (rx_data == 27)
	 {
		 resize_flag = 1;
		 UART0_C2 &=~ UART0_C2_RIE_MASK;

	 }
	 else
	 {
		 push(SMA,rx_data);
		 UART0_C2|=UART0_C2_TIE_MASK;
	 }
 }
 if (UART0_S1 & UART_S1_TDRE_MASK)
 {

//	 UART0->D=rx_data;
	 UART0_C2&=~UART0_C2_TIE_MASK;
 }


 __enable_irq();
}


void myprintf(char *str, ...)
{
	va_list ap;
	va_start (ap, str);
	int i = 0;

	while (str && str[i])
	{
		uart_tx(str[i]);
		i++;

		if(str[i] == '%')
		{
			i++;

			switch (str[i])
			{
			case 'd':

				number = va_arg (ap,int);
				divisor_check = number;
				divisor = 0;
				power = -1;
				send_count = 0;

				while (divisor_check!=0)
				{
					divisor_check = divisor_check/10;
					power++;
				}

				divisor = pow(10,power);

				while (divisor!=0)
				{
					send_count = number/divisor;
					number = number - send_count*divisor;
					divisor = divisor/10;
					// Convert to ASCII value
					send_count = send_count + 48;
					uart_tx(send_count);
				}
				break;

			case 'c':

				uart_tx(va_arg (ap,int));

				break;

			}
			i++;
		}
	}
va_end(ap);
}

