/*
 * checkEvenOrOdd.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Omar
 */


#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int num;
	printf("Enter an integer you want to check:");
	fflush(stdout);
	scanf("%d", &num);
	if(num % 2 )
	{
		printf("%d is odd.",num);
	}
	else
		printf("%d is even.",num);

	return 0;
}
