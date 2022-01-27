/*
 * FindLen.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Omar
 */


#define Size_Array 100

#include <stdio.h>
#include "string.h"
int main(){

	char str[Size_Array];

	int i=0;
	printf("Enter a string:");
	fflush(stdout);
	gets(str);


	while(str[i++]);


	printf("Length of String = %d ",i-1);

	return 0;
}

