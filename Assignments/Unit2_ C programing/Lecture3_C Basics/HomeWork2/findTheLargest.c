/*
 * findTheLargest.c
 *
 *  Created on: ??�/??�/????
 *      Author: Omar
 */



#include <stdio.h>
#include <stdlib.h>

int main(void) {
	float num1,num2,num3;
	printf("Enter three numbers:");
	fflush(stdout);
	scanf("%f %f %f", &num1,&num2,&num3);
	if(num1 > num2  )
	{
		if(num1 > num3 )
		  printf("Largest number = %f",num1);
		else  printf("Largest number = %f",num3);
	}
	else
		if(num2 > num3 )
		  printf("Largest number = %f",num2);
		else  printf("Largest number = %f",num3);


	return 0;
}
