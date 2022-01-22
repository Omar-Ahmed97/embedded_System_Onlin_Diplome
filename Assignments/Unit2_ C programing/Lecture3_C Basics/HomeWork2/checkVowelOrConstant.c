/*
 * checkVowelOrConstant.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Omar
 */

#include <stdio.h>
#include <stdlib.h>


int main(void) {
	char c;
	printf("Enter an alphabet:");
	fflush(stdout);
	scanf("%c", &c);
	if(c == 'a' || c == 'e' ||c == 'i' || c == 'o' || c == 'u' || c == 'A' || c == 'E' ||c == 'I' || c == 'O' || c == 'U' )
	{
		printf("%c is vowel.",c);
	}
	else
		printf("%c is consonant.",c);

	return 0;
}
