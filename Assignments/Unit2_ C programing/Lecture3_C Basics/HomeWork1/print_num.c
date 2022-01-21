/*
 * print_num.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Omar
 */


#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int num;
	printf("Enter an integer:");
	fflush(stdin); fflush(stdout);
	scanf("%d", &num);
	fflush(stdin); fflush(stdout);
	printf("You entered:%d", num);

	return 0;
}
