/*
 * linkes_list.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: Omar
 */

#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "conio.h"

#define Dprintf(...)       {fflush(stdout);\
							fflush(stdin);\
							printf(__VA_ARGS__);\
							fflush(stdout);\
							fflush(stdin);}







//effective data
struct Sdata
{
	int ID;
	char name[40];
	float height;

};


struct SStudent
{
	struct Sdata student;
	struct SStudent *PNextStudent;
};



void reversNodes();

void findMiddle();
void getNth(int index);
void add_student();
int delete_student();
void view_student();
void deleteAll();
int printNumEle_rec(struct SStudent *head);
void printNumEle();
void findIndexBackward(int index);
#endif /* LINKED_LIST_H_ */
