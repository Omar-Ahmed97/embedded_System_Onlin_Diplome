/*
 * Queue.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Omar
 */


#include"Queue.h"


Queue_status Queue_init(Queue_type_t * head,Element_Type *base, unsigned int length)
{
	if(!base)
		return Queue_null;
	head->base = base;
	head->front = NULL;
	head->rear = NULL;
	head->count =0;
	head->length = length;

	return Queue_no_error;

}
Queue_status Queue_enqueue(Queue_type_t *head ,Element_Type item)
{
	if(!head->base)
		return Queue_null;
	if(head->length == head->count)
		return Queue_full;
	if(head->front == NULL)
		head->front = head->rear =  head->base;
	else
		if(head->front+1 >= head->base + head->length)
			head->front = head->base;
		else head->front++;
	*(head->front) = item;
	head->count++;

	return Queue_no_error;

}
Queue_status Queue_dequeue(Queue_type_t *head ,Element_Type* item)
{
	if(!head->base)
		return Queue_null;
	if( head->count == 0)
		return Queue_empty;

	*item = *(head->rear) ;

	if(head->rear+1 >= head->base + head->length)
		head->rear = head->base;
	else head->rear++;

	head->count--;

	return Queue_no_error;

}
Queue_status Queue_is_full(Queue_type_t *head )
{
	if(head->length == head->count)
		return Queue_full;
	return Queue_no_error;
}
Queue_status Queue_visit_all(Queue_type_t *head ,void (*pf)(Element_Type *temp,int rollNum,char *name, int cid, Element_Type **pptemp, Element_Type *student_list,int end),int rollNum,char *name , int cid ,Element_Type **pptemp, Element_Type *student_list)
{

	Element_Type* pass = head->rear ;

	int i;
	if(head->base == NULL)
		return Queue_null;




	for(i=0; i < head->count ;i++ ){
		if(i+1 == head->count) pf(pass,rollNum,name,cid,pptemp,student_list,1);
		else pf(pass,rollNum,name,cid,pptemp,student_list,0);
		if(pass+1 >= head->base + head->length)
			pass = head->base;
		else pass++;
	}


	/*
	if(e_type == by_fname && (*student_list).rollNum == NULL){
		return Queue_no_name;

	}
	else if(e_type == by_courseID && (*student_list).rollNum == NULL){
		return Queue_no_courses;

	}*/
	return Queue_no_error;
}
Queue_status Queue_rmNode(Queue_type_t *head ,Element_Type* item){

	Element_Type* current = item;
	Element_Type* next = item;
	if(!head->base)
		return Queue_null;
	if( head->count == 0)
		return Queue_empty;

	while( next != head->front ){

		if(next+1 >= head->base + head->length)
			next = head->base;
		else next++;
		*(current) = *next;
		current = next;

	}
	head->count--;
	if(head->count == 0)
	{
		head->front=NULL;
		head->rear = NULL;

	}
	else if(head->front == head->base)
		head->front = head->base + head->length-1;
	else head->front--;

	return Queue_no_error;
}
