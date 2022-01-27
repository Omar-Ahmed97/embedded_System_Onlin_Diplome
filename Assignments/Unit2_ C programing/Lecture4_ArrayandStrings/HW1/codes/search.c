/*
 * search.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Omar
 */




#define Size_Array 100

#include <stdio.h>
int main(){

	int arr[Size_Array];
	int num_data ,i,num;
	printf("Enter no of elements :");
	fflush(stdout);
	scanf("%d",&num_data);

	for(i = 0 ; i<num_data ;i++ )
	{
		arr[i] = 11*i;
		printf("%d ",arr[i]);
	}


	printf("\n Enter the element to be searched :");
	fflush(stdout);
	scanf("%d",&num);



		for(i = 0 ; i < num_data ;i++ )
		{
			if(arr[i] == num)
				break;

		}
		if(i == num_data )
			{
			printf("element not found ");
			return 0;
			}
		printf("element  found at location %d",i+1);
	return 0;
}
