/*
 * MultiplyFloatingNums.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Omar
 */


#include <stdio.h>
#include <stdlib.h>

int main(void) {
	float num1 , num2;
	printf("Enter two numbers:");
	fflush(stdin); fflush(stdout);
	scanf("%f %f", &num1, &num2);
	printf("\n Product:%f", num1*num2);
	return 0;
}
