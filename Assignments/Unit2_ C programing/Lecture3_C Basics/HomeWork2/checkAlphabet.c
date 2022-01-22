/*
 * checkAlphabet.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Omar
 */


#include <stdio.h>
#include <stdlib.h>

int main(void) {
	char c;
	printf("Enter a character:");
	fflush(stdout);
	scanf("%c", &c);
	if(c >= 'A' && c <= 'z'  )
	{
		printf("%c is alphabet.",c);
	}
	else
		printf("%c is not an alphabet.",c);

	return 0;
}
