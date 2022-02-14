/*
 * calArea.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Omar
 */


#include <stdio.h>


#define Pi 3.14
#define Area(r) (Pi*(r)*(r))

int main(){

	int radius;
	float area;


	printf("\nEnter Radius\n");
	fflush(stdout);
	scanf("%d",&radius);
	area =  Area(radius);
	printf("\nArea=%0.2f",area);

	return 0;
}

