/*
 * studentsData.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Omar
 */

#include <stdio.h>

typedef struct student{
	char name[50];
	int roll;
	float marks;

}Student;
int main(){

	Student s;

	printf("Enter name:");
	fflush(stdout);
	scanf("%s",&s.name);

	printf("Enter roll number:");
	fflush(stdout);
	scanf("%d",&s.roll);

	printf("Enter marks:");
	fflush(stdout);
	scanf("%f",&s.marks);

	printf("\nDisplaying Information\n");
	printf("name: %s\n",s.name);
	printf("Roll number: %d \n",s.roll);
	printf("Marks : %f\n",s.marks);
	return 0;
}

