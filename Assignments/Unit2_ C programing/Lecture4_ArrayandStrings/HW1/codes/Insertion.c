/*
 * Insertion.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Omar
 */



#define Size_Array 100

#include <stdio.h>
int main(){

	int arr[Size_Array];
	int num_data ,i,num,location;
	printf("Enter no of elements :");
	fflush(stdout);
	scanf("%d",&num_data);
	for(i = 0 ; i<num_data ;i++ )
	{
		arr[i] = i+1;
		printf("%d  ",arr[i]);
	}


	printf("\n Enter the element to be inserted :");
	fflush(stdout);
	scanf("%d",&num);

	printf("Enter the location :");
	fflush(stdout);
	scanf("%d",&location);

		for(i = num_data-1 ; i >= location-1 ;i-- )
		{
			arr[i+1] = arr[i];

		}
	arr[location-1] = num;
	num_data++;
	for(i = 0 ; i<num_data ;i++ )
	{

		printf("%d  ",arr[i]);
	}
	return 0;
}
