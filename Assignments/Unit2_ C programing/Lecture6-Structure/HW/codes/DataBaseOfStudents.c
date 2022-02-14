/*
 * DataBaseOfStudents.c
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

	Student s[10];
	int i=0;

	printf("Enter information of students:");
	for(i=0;i<10;i++){
		printf("\n for Roll number %d ",i+1);
		s[i].roll =i+1;

		printf("\nEnter name:");
		fflush(stdout);
		scanf("%s",&s[i].name);

		printf("Enter marks:");
		fflush(stdout);
		scanf("%f",&s[i].marks);
	}



	printf("\nDisplaying Information of Students\n");
	for(i=0;i<10;i++){
		printf("\nInformation for Roll number %d ",i+1);

		printf("\nname: %s\n",s[i].name);
		printf("Marks : %f\n",s[i].marks);
	}



	return 0;
}

