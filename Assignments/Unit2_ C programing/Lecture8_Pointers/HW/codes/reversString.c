/*
 * reversString.c
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
void reverse(char *pstr){

	int i=0;
	while( *pstr++ != '\0') i++;
	--pstr;
	while( i-- !=0){
		printf("%c",*--pstr);
	}



}
