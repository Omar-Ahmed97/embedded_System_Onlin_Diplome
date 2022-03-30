/*
 * PointerHanhling.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Omar
 */


#include <stdio.h>


int main(){

int m =29;

printf("Adress of m :%p\n",&m);
printf("value of m : %d\n",m);

int *ab = &m;

printf("Adress of pointer ab :%p\n",ab);
printf("content of pointer ab : %d\n",*ab);

*ab =7;

printf("Adress of m :%p\n",&m);
printf("value of m : %d\n",m);


	return 0;
}

