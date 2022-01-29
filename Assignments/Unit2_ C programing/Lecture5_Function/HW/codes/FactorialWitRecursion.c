/*
 * FactorialWitRecursion.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Omar
 */


#include <stdio.h>

double Fact(int fact);

int main(){

	int fact;

	printf("Enter a positiv integr:");
	fflush(stdout);
	scanf("%d",&fact);
	printf("Factorial of %d = %0.2fl ", fact,Fact(fact));

	return 0;
}

double Fact(int fact){

	if(fact < 1)
		return 1;
	else return fact *Fact(fact-1);

}
