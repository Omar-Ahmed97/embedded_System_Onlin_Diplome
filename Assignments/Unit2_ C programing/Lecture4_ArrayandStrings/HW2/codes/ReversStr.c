/*
 * ReversStr.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Omar
 */

#define Size_Array 100

#include <stdio.h>
#include "string.h"
int main(){

	char str1[Size_Array];
	char str2[Size_Array];

	int i=0,j=0;
	printf("Enter the string:");
	fflush(stdout);
	gets(str1);

	i = strlen(str1);
	while( i >=0){

		str2[j++] = str1[--i];
	}

	str2[j]= '\0';
	printf("Reverse String1 is ");
	puts(str2);

	printf("Reverse String2 is ");

	for(i = strlen(str1)-1; i>=0 ; i--){

		printf("%c",str1[i]);
	}




	return 0;
}
