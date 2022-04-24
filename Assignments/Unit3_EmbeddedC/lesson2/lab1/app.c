#include "uart.h"

unsigned char strinf_buffer[100]="Learn-in-depth:Omar ";

void main(void)
{
	Uart_Send_string(strinf_buffer);
}