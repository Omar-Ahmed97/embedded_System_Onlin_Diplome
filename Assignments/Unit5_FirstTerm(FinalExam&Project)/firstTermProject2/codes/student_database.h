/*
 * student_database.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: Omar
 */

#ifndef STUDENT_DATABASE_H_
#define STUDENT_DATABASE_H_



#include"Queue.h"
#include"stdio.h"
#include"stdlib.h"
#include"string.h"


#define SIZE 50
#define no_courses 5
#define DPRINTF(...)  fflush(stdin); fflush(stdout); printf(__VA_ARGS__);fflush(stdin); fflush(stdout)



 struct Sstudent{
	char fname[50];
	char lname[50];
	int rollNum;
	float gpa;
	int courseID[no_courses];
};

 typedef struct Sstudent SStudent_t;

 SStudent_t Student_list[SIZE];

typedef enum{
	by_rollNum,
	by_fname,
	by_courseID

}comparison_type;

void add_student_file();
void add_student_manually();
void find_by_rollNum();
void find_by_fnum();
void find_by_courseID();
void find_totla_numStudent();
void delet_student();
void update_student();
void show_students();

#endif /* STUDENT_DATABASE_H_ */
