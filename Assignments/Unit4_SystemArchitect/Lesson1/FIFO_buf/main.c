/*
 * main.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Omar
 */

#include "fifo.h"

int main()
{
	FIFO_Buf_t FIFO_UART;
	element_type i,temp;
	if( FIFO_init( &FIFO_UART , uart_buff,5) == FIFO_no_error )
		printf("fifo init --------Done \n");

	for(i=0 ; i<7 ; i++){
		printf("\t FIFO_UART enqueue: (%x) \n",i);
		if( FIFO_enqueue(&FIFO_UART , i) == FIFO_no_error)
		printf(" FIFO_UART Enqueue Done\n");

		else printf("FIFO_UART Enqueue Faild\n");
	}

	FIFO_print( &FIFO_UART);

	for(i=0 ; i<7 ; i++){
		if(	FIFO_dequeue(&FIFO_UART , &temp) == FIFO_no_error)
		printf("FIFO_dequeue get: %d ------DONE \n",temp);
	}

	for(i=0 ; i<7 ; i++){
		if(	FIFO_dequeue(&FIFO_UART , &temp) == FIFO_no_error)
		printf("FIFO_dequeue get: %d ------DONE \n",temp);
	}

	FIFO_print( &FIFO_UART);

return 0;
}
