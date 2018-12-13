/****************************************************************
 * Author : Satya Mehta and Siddhant Jajoo
 * UART Initialization and ISR
 *
 */



#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include "MKL25Z4.h"
//#include "board.h"
#include "uart.h"



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
	UART0_C2 |= (UART0_C2_TE_MASK); //transmitter enable
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

void uart_tx_irq(int8_t data)
{
	UART0_C2|=(UART0_C2_TIE_MASK);
	UART0->D = data;
	while(!(UART0->S1 & UART_S1_TC_MASK)); //Waiting for transmission to get complete
	UART0_C2&=~UART0_C2_RIE_MASK; //Disable rx interrupt

}


int8_t uart_rx()
{
	int8_t data;
	while((UART0->S1 & UART_S1_RDRF_MASK) == 0);
	data = UART0->D;
	return data;
}




//void UART0_IRQHandler()
//{
//__disable_irq();
//
// if (UART0_S1 & UART_S1_RDRF_MASK)
// {
//	 rx_data=UART0->D;
//	 push(SMA,rx_data);
// }
//
// if (UART0_S1 & UART_S1_TDRE_MASK)
// {
//	 tx_flag = 1;						//Scheduler Flag
//	 UART0_C2&=~UART0_C2_TIE_MASK;		//Disabling Tx interrupts
//	 UART0_C2|=UART0_C2_RIE_MASK;
// }
//
// __enable_irq();
//}


/*Printf Function*/
void myprintf(char *str, ...)
{
	va_list ap;
	va_start (ap, str);
	int i = 0;

	while (str && str[i])
	{
		uart_tx_irq(str[i]);
		i++;

		if(str[i] == '%')
		{
			i++;

			switch (str[i])
			{
			case 'd':
				number = va_arg (ap,int);
				if(number & 0x8000)
				{
					number = (~number) + (0x0001);
					uart_tx_irq(45);
				}
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
					uart_tx_irq(send_count);
				}
				break;

			case 'f':
				db = va_arg(ap,double);
//				number = db;
//				float x = (float)db;
				if(db < 0)
				{
					db = db * (-1);
					uart_tx_irq(45);
				}
				number1 = (uint16_t)db;
				myprintf(" %d",number1);
				uart_tx_irq(46);
				number1 = (uint16_t)((db - number1) * 100);
				myprintf(" %d\r\n", number1);
				break;

			case 'c':
				uart_tx_irq(va_arg (ap,int));
				break;

			}
			i++;
		}
	}
va_end(ap);
}

