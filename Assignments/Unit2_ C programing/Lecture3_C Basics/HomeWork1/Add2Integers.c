/*
 * Add2Integers.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Omar
 */


#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int num1 , num2;
	printf("Enter two integers:");
	fflush(stdin); fflush(stdout);
	scanf("%d %d", &num1, &num2);
	printf("\n Sum:%d", num1+num2);
	return 0;
}
