/*
 * FindTransposeOfMat.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Omar
 */
#define MAX_ROWS 100
#define MAX_COLS 100


#include <stdio.h>
int main(){
	float mat1[MAX_ROWS][MAX_COLS];
	int row,col,r,c;
	printf("Enter rows and colums of matrix");
	fflush(stdout);
	scanf("%d %d",&row,&col);

	for(r=0 ; r<row ; r++ )
	{
		for(c=0; c<col; c++)
		{
			printf("Enter element a%d%d: ",r+1,c+1);
			fflush(stdout);
			scanf("%f",&mat1[r][c]);

		}
	}

	printf("Entered matrix:\n");

	for(r=0 ; r<row ; r++ )
	{
		for(c=0; c<col; c++)
		{
			printf("%0.2f\t",mat1[r][c]);

		}
		printf("\n");
	}

	printf("Transpose of matrix:\n");

	for(c=0 ; c<col ; c++ )
	{
		for(r=0; r<row; r++)
		{
			printf("%0.2f\t",mat1[r][c]);

		}
		printf("\n");
	}

	return 0;
}

