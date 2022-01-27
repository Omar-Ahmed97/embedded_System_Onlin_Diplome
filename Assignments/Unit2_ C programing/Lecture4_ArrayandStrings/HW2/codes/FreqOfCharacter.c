/*
 * FreqOfCharacter.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Omar
 */



#define Size_Array 100

#include <stdio.h>
#include "string.h"
int main(){

	char str[Size_Array];
	char frq_ch,num=0;
	int i;
	printf("Enter a string:");
	fflush(stdout);
	gets(str);

	printf("Enter a character to find frequency:");
	fflush(stdout);
	scanf("%c",&frq_ch);

	for(i = 0 ; i<strlen(str) ;i++ )
	{
		if(str[i] == frq_ch)
			num++;
	}

	printf("Frequency of %c = %d ",frq_ch,num);

	return 0;
}

