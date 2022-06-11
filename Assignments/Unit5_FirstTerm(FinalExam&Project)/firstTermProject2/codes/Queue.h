/*
 * Queue.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: Omar
 */

#ifndef QUEUE_H_
#define QUEUE_H_

#include "stdio.h"
#include "stdint.h"
#include "student_database.h"



#define Element_Type  struct Sstudent

typedef struct{

	unsigned int count;
	unsigned int length;
	Element_Type *base;
	Element_Type *front;
	Element_Type *rear;

}Queue_type_t;

typedef enum {
	Queue_no_error,
	Queue_full,
	Queue_empty,
	Queue_null,
	Queue_duplicate_roll,
	Queue_no_rollNum,
	Queue_no_name,
	Queue_no_courses
}Queue_status;

Queue_status Queue_init(Queue_type_t * ,Element_Type *base, unsigned int length);
Queue_status Queue_enqueue(Queue_type_t * ,Element_Type item);
Queue_status Queue_dequeue(Queue_type_t * ,Element_Type* item);
Queue_status Queue_rmNode(Queue_type_t * ,Element_Type* item);
Queue_status Queue_is_full(Queue_type_t * );
Queue_status Queue_visit_all(Queue_type_t *head ,void (*pf)(Element_Type *temp,int rollNum,char *name, int cid, Element_Type **pptemp, Element_Type *student_list,int end),int rollNum,char *name , int cid ,Element_Type **pptemp, Element_Type *student_list);

#endif /* QUEUE_H_ */
