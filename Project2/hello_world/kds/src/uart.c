#include "MKL25Z4.h"
#include "uart.h"
#include <stdint.h>
#include "board.h"
#include <stdlib.h>


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



void uart_tx(uint8_t data)
{

	while(!(UART0->S1 & UART_S1_TDRE_MASK)); //Waiting for the buffer to get empty
	UART0->D = data;
	while(!(UART0->S1 & UART_S1_TC_MASK)); //Waiting for transmission to get complete

}

uint8_t uart_rx()
{
	uint8_t data;
	while((UART0->S1 & UART_S1_RDRF_MASK) == 0);
	data= UART0->D;
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
