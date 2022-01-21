/*
 * SwapingNums.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Omar
 */


#include <stdio.h>
#include <stdlib.h>

int main(void) {
	float a , b ,c;
	printf("Enter value of a:");
	 fflush(stdout);
	scanf("%f", &a);

	printf("Enter value of b:");
	fflush(stdout);
	scanf("%f", &b);

	c=a;
	a=b;
	b=c;

	printf("After Swapping value of a:%f\n",a);
	fflush(stdin); fflush(stdout);
	printf("After Swapping value of b:%f",b);
	fflush(stdin); fflush(stdout);
	return 0;
}
