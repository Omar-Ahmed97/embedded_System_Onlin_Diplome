/*
 * SumOfMat.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Omar
 */
/*
 * SumOfMatrix.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Omar
 */


#include <stdio.h>
int main(){
	float mat1[2][2],mat2[2][2],mat3[2][2];
	int r,c;
	printf("Enter the elements of 1st matrix");

	for(r=0 ; r<2 ; r++ )
	{
		for(c=0; c<2; c++)
		{
			printf("Enter a%d%d: ",r+1,c+1);
			fflush(stdout);
			scanf("%f",&mat1[r][c]);

		}
	}

	printf("Enter the elements of 2nd matrix");

	for(r=0 ; r<2 ; r++ )
	{
		for(c=0; c<2; c++)
		{
			printf("Enter b%d%d: ",r+1,c+1);
			fflush(stdout);
			scanf("%f",&mat2[r][c]);

		}
	}

	printf("sum of  matrix\n");

	for(r=0 ; r<2 ; r++ )
	{
		for(c=0; c<2; c++)
		{
			printf(" %0.2f \t",mat2[r][c]+mat1[r][c]);


		}
		printf("\n");

	}
	return 0;
}


