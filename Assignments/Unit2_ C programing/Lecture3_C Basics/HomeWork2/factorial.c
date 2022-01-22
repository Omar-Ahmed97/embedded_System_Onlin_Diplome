/*
 * factorial.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Omar
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int num ,fact ;
	printf("Enter an integer:");
	 fflush(stdout);
	scanf("%d", &num);
	for(fact =num-1 ; fact>=2 ; fact--)
		num *= fact;
	printf("\n factorial = %d", num);
	return 0;
}
