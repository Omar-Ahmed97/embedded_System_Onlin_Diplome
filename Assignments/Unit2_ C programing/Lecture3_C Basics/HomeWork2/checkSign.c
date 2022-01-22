/*
 * checkSign.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Omar
 */


#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int num;
	printf("Enter a number:");
	fflush(stdout);
	scanf("%d", &num);
	if(num > 0 )
	{
		printf("%d is positive.",num);
	}
	else if(num < 0 )
		printf("%d is negative.",num);
	else printf("you entered 0.");

	return 0;
}
