#include "uart.h"

#define UART0DR *((volatile unsigned int * )(0x101f1000))

void Uart_Send_string(unsigned char * p_tx_string)
{
	while(*p_tx_string){

		UART0DR = (unsigned int)(*p_tx_string);
		p_tx_string++;

	}
}