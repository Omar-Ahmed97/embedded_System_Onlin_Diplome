/*
 * calculator.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Omar
 */


#include <stdio.h>
#include <stdlib.h>

int main(void) {
	float num1 , num2;
	char op;
	printf("Enter operator either + or - or * or / :");
	 fflush(stdout);
	scanf("%c", &op);

	printf("Enter two operands :");
	 fflush(stdout);
	scanf("%f %f", &num1, &num2);
	switch(op)
	{
	case '+': printf("\n %f+%f = %f",num1 ,num2, num1+num2);  break;
	case '-':  printf("\n %f-%f = %f",num1 ,num2, num1-num2); break;
	case '*':  printf("\n %f*%f =%f", num1 ,num2,num1*num2); break;
	case '/': printf("\n %f/%f =%f", num1 ,num2, num1/num2);  break;
	default: printf("you have Entered wrong operator :");

	}

	return 0;
}
