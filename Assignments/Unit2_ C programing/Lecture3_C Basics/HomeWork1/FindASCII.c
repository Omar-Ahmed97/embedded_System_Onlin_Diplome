/*
 * FindASCII.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Omar
 */


#include <stdio.h>
#include <stdlib.h>

int main(void) {
	char c;
	printf("Enter a character :");
	 fflush(stdout);
	scanf("%c", &c);
	printf("ASCII value of %c is :%d", c,c);

	return 0;
}
