/*
 * calculatePower.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Omar
 */


#include <stdio.h>

double Power(int base,int power);

int main(){

	int base,power;

	printf("Enter base number:");
	fflush(stdout);
	scanf("%d",&base);
	printf("Enter power number(positive integer) :");
	fflush(stdout);
	scanf("%d",&power);
	printf("%d^%d=%0.2lf",base,power,Power(base,power));

	return 0;
}

double Power(int base,int power){

	if(power < 1)
		return 1;
	else return base *Power(base,power-1);

}
