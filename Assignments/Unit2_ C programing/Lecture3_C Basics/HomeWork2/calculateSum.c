/*
 * calculateSum.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Omar
 */



#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int num,i;
	printf("Enter an integer:");
	 fflush(stdout);
	scanf("%d", &num);
	for(i=num-1 ; i>=1 ; i--)
		num += i;
	printf("\n Sum = %d", num);
	return 0;
}
