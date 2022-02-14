/*
 * AddTwoDis.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Omar
 */


#include <stdio.h>

typedef struct distance{
	int feet;
	float inchs;

}Distance;

Distance enterInfo(int num);
Distance sum(Distance d1,Distance d2);
int main(){

	Distance d1,d2,d3;

	d1 = enterInfo(1);
	d2 = enterInfo(2);
	d3=sum(d1,d2);
	printf("\nSum of Distances= %d feet %f inchs:",d3.feet,d3.inchs);
	return 0;
}

Distance enterInfo(int num){
	Distance d1;

	printf("\nEnter Information for %s distance",(num==1)?"1st":"2nd");
	printf("\nEnter feet:");
	fflush(stdout);
	scanf("%d",&d1.feet);
	printf("Enter inch:");
	fflush(stdout);
	scanf("%f",&d1.inchs);
	return  d1;

}
Distance sum(Distance d1,Distance d2){
	Distance d3;
	d3.feet = d1.feet +d2.feet;
	d3.inchs = d1.inchs +d2.inchs;
	if(d3.inchs >=12){
		d3.feet += (int)(d3.inchs /12);
		d3.inchs -= (int)(d3.inchs /12) * 12;
	}
	return d3;
}
