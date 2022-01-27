/*
 * CalculateAvgUsingArr.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Omar
 */

#define Size_Array 100

#include <stdio.h>
int main(){

	float arr[Size_Array],sum=0;
	int num_data ,i;
	printf("Enter The numbers of data :");
	fflush(stdout);
	scanf("%d",&num_data);
	for(i = 0 ; i<num_data ;i++ )
	{
		printf("%d. Enter number :",i+1);
		fflush(stdout);
		scanf("%f",&arr[i]);
		sum+=arr[i];

	}

	printf("Averge = %0.2f", sum/i );
	return 0;
}
