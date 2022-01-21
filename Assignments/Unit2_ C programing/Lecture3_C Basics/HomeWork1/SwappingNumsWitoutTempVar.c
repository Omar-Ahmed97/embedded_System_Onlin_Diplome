/*
 * SwappingNumsWitoutTempVar.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Omar
 */


#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int a , b ,c;
	printf("Enter value of a:");
	 fflush(stdout);
	scanf("%d", &a);

	printf("Enter value of b:");
	fflush(stdout);
	scanf("%d", &b);

//	a = a+b;
//	b= a-b;
//	a= a-b;
//
	a ^= b;
	b ^=a;
	a^=b;
	printf("After Swapping value of a:%d\n",a);
	fflush(stdin); fflush(stdout);
	printf("After Swapping value of b:%d",b);
	fflush(stdin); fflush(stdout);
	return 0;
}
