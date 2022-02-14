/*
 * AddTwoComplex.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Omar
 */

#include <stdio.h>

typedef struct complex{
	float real;
	float imag;

}Complex;

Complex enterInfo(int num);
Complex sum(Complex d1,Complex d2);
int main(){

	Complex c1,c2,c3;

	c1 = enterInfo(1);
	c2 = enterInfo(2);
	c3=sum(c1,c2);
	printf("\nSum = %0.2f + %0.2f i:",c3.real,c3.imag);
	return 0;
}

Complex enterInfo(int num){
	Complex c1;

	printf("\nEnter Information for %s complex number",(num==1)?"1st":"2nd");
	printf("\nEnter real and imaginary respectively:");
	fflush(stdout);
	scanf("%f %f",&c1.real,&c1.imag);


	return  c1;

}
Complex sum(Complex c1,Complex c2){
	Complex c3;
	c3.real = c1.real +c2.real;
	c3.imag = c1.imag +c2.imag;

	return c3;
}

