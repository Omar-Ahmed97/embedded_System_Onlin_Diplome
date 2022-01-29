/*
 * Reverse.c
 *
 *  Created on: ??ş/??ş/????
 *      Author: Omar
 */


#include <stdio.h>
#include <stdlib.h>

void reverse(char str[]);
int main(){

	char str[100];

	printf("Enter a sentence:");
	fflush(stdout);
	gets(str);

	reverse(str);

	return 0;
}
void reverse(char str[]){

	if(str[0] == '\0')
		;
	else 	reverse(str+1);
	printf("%c",str[0]);
}
