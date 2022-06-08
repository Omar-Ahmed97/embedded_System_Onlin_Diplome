/*
 * main.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Omar
 */


#include "lifo.h"
#include "stdio.h"

unsigned int buf1[5];

int main()
{
	int i , temp;
	LIFO_Buf_t uart_lifo , I2C_lifo;
	//static allocation
	LIFO_init(&uart_lifo , buf1 , 5);
	//dynamic allocation
	unsigned int *buf2 = (unsigned int*) malloc(5 * sizeof(unsigned int));
	LIFO_init(&I2C_lifo , buf2 , 5);

	for(i=0 ; i<5 ; i++){
		if( LIFO_Add_item(&uart_lifo , i) == LIFO_no_error)
		printf("UART_LIFO add: %d \n",i);
	}

	for(i=0 ; i<5 ; i++){
		if(	LIFO_get_item(&uart_lifo , &temp) == LIFO_no_error)
		printf("UART_LIFO get: %d \n",temp);
	}

return 0;
}
