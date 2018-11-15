
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

#include "MKL25Z4.h"
#include "board.h"
#include "uart.h"
#include "circbuff.h"


#define OSR_VAL (16)
#define SYS_CLOCK (48000000)
#define BAUD (115200)


void uart_init()
{

	/*Clock Enable*/
	SIM->SCGC4 |= SIM_SCGC4_UART0_MASK; //turn ON clock gate
	//SIM->SOPT2 &= ~SIM_SOPT2_UART0SRC_MASK;
	SIM->SOPT2 |= 0x4000000; //FLL or PLL Clock

	/*Enable ALT2 Pins*/
	/*UART RX/TX connected to Port A*/


	UART0_C2 &= ~(UART0_C2_TE_MASK | UART0_C2_RE_MASK);

	UART0->C1 &= ~(UART0_C1_M_MASK | UART0_C1_PE_MASK);
	UART0->BDH &= ~UART_BDH_SBNS(1);


//    UART0_C2 = 0;
//    UART0_C1 = 0;
//    UART0_C3 = 0;
//    UART0_S2 = 0;

	/*Baud Config*/
	uint16_t SBR=((SystemCoreClock)/(OSR_VAL*BAUD));
	UART0_C4=UART0_C4_OSR(0x0F);
	UART0_BDH= ((SBR>>8)& UART0_BDH_SBR_MASK);
	UART0_BDL=(SBR & UART0_BDL_SBR_MASK);
	//UART0->BDH &= 0x00;
	//UART0->BDL = 0x17;
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK; //enable PORTA
	PORTA_PCR1 = PORT_PCR_MUX(2);
	PORTA_PCR2 = PORT_PCR_MUX(2);
//	UART0->C2 |= UART_C2_RE(1) | UART_C2_TE(1);

	/*Enable Transmitter, Receiver and Receiver interrupt*/
	UART0_C2 |= (UART0_C2_TE_MASK)|(UART_C2_RE_MASK); //transmitter enable, Receiver enable
	//UART0_C2 |= UART0_C2_TIE_MASK;
	/*Enable IRQ*/
//	__enable_irq();

//	NVIC_EnableIRQ(UART0_IRQn);
}



void uart_tx(int8_t data)
{

	while(!(UART0->S1 & UART_S1_TDRE_MASK)); //Waiting for the buffer to get empty
	UART0->D = data;
	while(!(UART0->S1 & UART_S1_TC_MASK)); //Waiting for transmission to get complete

}

int8_t uart_rx()
{
	uint8_t data;
	while((UART0->S1 & UART_S1_RDRF_MASK) == 0);
	data = UART0->D;
	push(SMA,data);
	return data;
}

void UART0_IRQHandler()
{
__disable_irq();
int status;
 status = UART0_S1;
 if (status & UART_S1_TDRE_MASK)
 {
	uint8_t data= 5;
//	uart_tx(data);
	}


 __enable_irq();
}

/*
void myscanf(char * str,...)
{
va_list bp;
va_start (bp, str);
int i = 0;
int j = 0;
int k = 0;
char arr[100] = {0};
while (str && str[i])
{
	if(str[i] == '%')
		i++;
	{
		switch (str[i])
		{
		case 'c':
			while(1)
			{
				arr[j] = uart_rx();
				uart_tx(arr[j]);
				j++;
				if (arr[j-1] == 13)
				{
					arr[j] = NULL;
					uart_tx(10);
					break;
				}

			}
			*(char*)va_arg(bp,char*) = arr;
			i++;
			break;
		}
	}
}
va_end(bp);
}
*/

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

//
//			case 's':
//
//				while (va_arg(ap,int)!=NULL)
//				{
//					uart_tx(va_arg(ap,int));
//				}
//				break;

			}
			i++;

		}
	}
va_end(ap);
}

