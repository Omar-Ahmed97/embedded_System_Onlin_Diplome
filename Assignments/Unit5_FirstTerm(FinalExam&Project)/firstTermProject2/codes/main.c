/*
 * main.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Omar
 */

//roll number 0 is forbidden

#include"student_database.h"

int main(){

	int choice;

	DPRINTF("Welcome to the student mangement system\n");
	while(1){

		DPRINTF("Choose the task that you want to perform\n");
		DPRINTF("1. Add the student details manually\n");
		DPRINTF("2. Add the student details from text file\n");
		DPRINTF("3. Find the student details by roll number \n");
		DPRINTF("4. Find the student details by first name\n");
		DPRINTF("5. Find the student details by course ID\n");
		DPRINTF("6. Find the total number of students\n");
		DPRINTF("7. Delete the students details by roll number\n");
		DPRINTF("8. Update the students details by roll number\n");
		DPRINTF("9. Show all information\n");
		DPRINTF("10. To Exit\n");
		DPRINTF("Enter your choice to perform the task: ");
		scanf("%d",&choice);



		switch(choice){

		case 1:
			add_student_manually();
			break;
		case 2:
		add_student_file();
			break;
		case 3:
			find_by_rollNum();
			break;
		case 4:
			find_by_fnum();
			break;
		case 5:
			find_by_courseID();
			break;
		case 6:
			find_totla_numStudent();
			break;
		case 7:
			delet_student();
			break;
		case 8:
			update_student();
			break;
		case 9:
			show_students();
			break;
		case 10:
			return 0;
			break;
		default :
			DPRINTF("This choice is wrong please enter another one\n");
			break;
		}
	}
	return 0;
}
