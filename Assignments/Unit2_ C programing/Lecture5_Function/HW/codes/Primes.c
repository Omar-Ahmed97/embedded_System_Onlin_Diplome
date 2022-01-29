/*
 * Primes.c
 *
 *  Created on: ??ş/??ş/????
 *      Author: Omar
 */

#include <stdio.h>
#include "math.h"
void primes(int start,int end);

int main(){

	int start,end;

	printf("Enter two numbers(intervals):");
	fflush(stdout);
	scanf("%d%d",&start,&end);

	primes(start,end);

	return 0;
}

void primes(int start,int end){
	int i;
	printf("Prime numbers between %d and %d are:  ",start,end);
	while(start <= end ){
		for(i=2 ; i <= sqrt(start) ;i++){
			if(start % i ==0)
				break;

		}
		if(i > sqrt(start))
			printf("%d ",start);
		start++;
	}

}
