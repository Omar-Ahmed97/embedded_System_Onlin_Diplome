/*
 * fifo.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Omar
 */

#include "fifo.h"



FIFO_Buf_status FIFO_init(FIFO_Buf_t* fifo, element_type* buf,uint32_t length)
{
	if(buf == NULL)
		return FIFO_null;
	fifo->base = buf;
	fifo->head = buf;
	fifo->tail = buf;
	fifo->length = length;
	fifo->count =0;

	return FIFO_no_error;

}
FIFO_Buf_status FIFO_enqueue(FIFO_Buf_t* fifo, element_type  item )
{
	if(!fifo->base  || !fifo->head  || !fifo->tail )
		return FIFO_null;

	//fifo is full
	if(FIFO_IS_FULL(fifo) == FIFO_full)
		return FIFO_full ;
	*(fifo->head) = item;
	if(fifo->head + 1 == fifo->base + fifo->length )
		fifo->head  = fifo->base;
	else
		fifo->head++;
	fifo->count++;

	return FIFO_no_error;

}
FIFO_Buf_status FIFO_dequeue(FIFO_Buf_t* fifo, element_type* item)
{
	if(!fifo->base  || !fifo->head  || !fifo->tail )
		return FIFO_null;

	//fifo is empty
	if(fifo->count == 0)
		return FIFO_empty ;
	*item = *(fifo->tail);
	fifo->count--;

	if(fifo->tail + 1 == fifo->base + fifo->length )
		fifo->tail  = fifo->base;
	else
		fifo->tail++;


	return FIFO_no_error;


}
FIFO_Buf_status FIFO_IS_FULL(FIFO_Buf_t* fifo)
{
	if(!fifo->base  || !fifo->head  || !fifo->tail )
		return FIFO_null;

	//fifo is full
	if(fifo->length == fifo->count )
		return FIFO_full ;
	return FIFO_no_error;

}
void FIFO_print(FIFO_Buf_t* fifo)
{
	element_type* temp;
	int i;
	if(fifo->count == 0)
	{
		printf("fifo is empty \n");
	}
	else{
		temp = fifo->tail;
		printf(" =============fifo_print============\n");
		for(i=0; i < fifo->count ;i++ ){
			printf("\t %X \n",*temp++);
		}
		printf("\n =======================\n");
	}

}
