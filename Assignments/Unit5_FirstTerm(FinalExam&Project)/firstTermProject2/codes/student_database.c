/*
 * student_database.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Omar
 */
#include"student_database.h"

unsigned int init_Queue_done=0;
Queue_type_t Queue_student;

void Display_StudentData(Element_Type *temp){

	DPRINTF("--------------------------\n");
	DPRINTF("The student's details are\n");
	DPRINTF("The first name is %s\n",temp->fname);
	DPRINTF("The last name is %s\n",temp->lname);
	DPRINTF("The GPA is %.2f\n",temp->gpa);
	DPRINTF("The course ID of each course\n");
	int i;
	for(i = 0; i < 5; i++){
		DPRINTF(" The course ID is: %d\n",temp->courseID[i]);
	}
	DPRINTF("--------------------------\n");
}

void check_unique(Element_Type *temp,int rollNum,char *name, int cid,Element_Type **pptemp, Element_Type *student_list,int end)
{

	static int index=0;
	int i;
	if(rollNum){
		if(temp->rollNum == rollNum)
		{
			*(student_list+index) = *temp;
			if(pptemp) *pptemp = temp;
		}
	}else if(cid){
		for(i=0; i< no_courses ; i++){
			if(temp->courseID[i] == cid)
				*(student_list+index++) = *temp;
		}
	}
	else if(name){
		if(stricmp(temp->fname , name)==0)
			*(student_list+index++) = *temp;
	}
	else Display_StudentData(temp);

	if(end) index=0;

}

void find_totla_numStudent(){
	if(init_Queue_done){
		DPRINTF("--------------------------\n");
		DPRINTF("[INFO] Total number of students is %d\n",Queue_student.count);
		DPRINTF("[INFO] You can add up to %d students\n",Queue_student.length);
		DPRINTF("[INFO] You can add %d more students\n",Queue_student.length-Queue_student.count);
		DPRINTF("--------------------------\n");
		DPRINTF("--------------------------\n");
	}
	else{
		DPRINTF("[ERROR] Students database is empty or not yet initialized\n");
	}
}
Queue_status add_student_display(SStudent_t *pstudent)
{
	Element_Type student_list[SIZE]={{NULL,NULL,0,0,NULL}};

	DPRINTF("--------------------------\n");
	DPRINTF("ADD The Students Details\n");
	DPRINTF("--------------------------\n");

	DPRINTF("Enter The roll Number\n");
	scanf("%d",&pstudent->rollNum);
	DPRINTF("Enter The first name of the student\n");
	scanf("%s",pstudent->fname);
	DPRINTF("Enter The last name of the student\n");
	scanf("%s",pstudent->lname);
	DPRINTF("Enter The GPA of the student\n");
	scanf("%f",&pstudent->gpa);
	DPRINTF("Enter The Course ID of each Course\n");
	int i;
	for( i=0; i < no_courses ; i++){
		DPRINTF("Course %d id: ",i+1);
		scanf("%d",&pstudent->courseID[i]);
	}

	Queue_visit_all(&Queue_student , check_unique,pstudent->rollNum,NULL,0,NULL,student_list);
	if(student_list[0].rollNum){
		return Queue_duplicate_roll;
	}
	else Queue_enqueue(&Queue_student,*pstudent);
	return Queue_no_error;
}
void add_student_file(){
	Element_Type student_list[SIZE]={{NULL,NULL,0,0,NULL}};
	SStudent_t student;
	int count =0;
	if(!init_Queue_done){
		if(Queue_init(&Queue_student,Student_list, SIZE)==Queue_no_error){
			init_Queue_done = 1;
		}else
		{DPRINTF("Error in initialization\n");}
	}


	FILE *fp;

	fp=fopen("students.txt","r");
	if(!fp){
		DPRINTF("Couldn't read file\n");
	}
	else{
		while(fscanf(fp,"%d %s %s %f %d %d %d %d %d[^\n]",&(student.rollNum),student.fname,student.lname,
				&(student.gpa),&(student.courseID[0]),&(student.courseID[1]),
				&(student.courseID[2]),&(student.courseID[3]),&(student.courseID[4]))!=EOF){
			Queue_visit_all(&Queue_student , check_unique,student.rollNum,NULL,0,NULL,student_list);
			if(student_list[0].rollNum){
				DPRINTF("[ERROR] Roll number %d is already taken\n",student.rollNum);

			}
			else{
				if(Queue_enqueue(&Queue_student,student) == Queue_full)
				{DPRINTF("[ERROR]  Students database is full\n");}
				else
				{
					DPRINTF("[INFO] Roll number %d saved successfully\n",student.rollNum);
				count++;
				}
			}

		}
		if(count > 0){
			DPRINTF("[INFO] Students details were added successfully\n");
		}
		find_totla_numStudent();
	}
	fclose(fp);

}
void add_student_manually(){
	SStudent_t student;
	if(!init_Queue_done){
		if(Queue_init(&Queue_student,Student_list, SIZE)==Queue_no_error){
			init_Queue_done = 1;
		}else
		{DPRINTF("Error in initialization\n");}
	}

	switch(add_student_display(&student)){

	case Queue_full:
		DPRINTF("[ERROR]  Students database is full\n");
		break;
	case Queue_duplicate_roll:
		DPRINTF("[ERROR] Roll number %d is already taken\n",student.rollNum);
		break;
	case Queue_no_error:
		DPRINTF("[INFO] Student details was added successfully\n");
		break;
	}

	find_totla_numStudent();
}

void find_by_rollNum(){
	int rollNum;
	Element_Type student_list[SIZE]={{NULL,NULL,0,0,NULL}};

	DPRINTF("Enter the roll number of the student: ");
	scanf("%d",&rollNum);
	switch(Queue_visit_all(&Queue_student , check_unique,rollNum,NULL,0,NULL,student_list)){
	case Queue_null:
		DPRINTF("[ERROR] Students database is empty or not yet initialized\n");
		break;
	}
	if(student_list[0].rollNum){
		return Display_StudentData(student_list);
	}
	else {DPRINTF("[ERROR] Roll number %d was not found\n",rollNum);}

}

void find_by_courseID()
{
	int cid;
	int i=0;
	Element_Type student_list[SIZE]={{NULL,NULL,0,0,NULL}};

	DPRINTF("Enter the course ID: ");
	scanf("%d",&cid);
	switch(Queue_visit_all(&Queue_student , check_unique,0,NULL,cid,NULL,student_list)){
	case Queue_null:
		DPRINTF("[ERROR] Students database is empty or not yet initialized\n");
		break;
	}
	if(!student_list[0].rollNum){
		{DPRINTF("[ERROR]Course ID %d was not found\n",cid);}
	}
	else {while(student_list[i].rollNum){
		Display_StudentData(student_list+i);
		i++;
	}}
}


void find_by_fnum()
{
	char name[50];
	int i=0;
	Element_Type student_list[SIZE]={{NULL,NULL,0,0,NULL}};

	DPRINTF("Enter first name of The students: ");
	gets(name);
	switch(Queue_visit_all(&Queue_student , check_unique,0,name,0,NULL,student_list)){
	case Queue_null:
		DPRINTF("[ERROR] Students database is empty or not yet initialized\n");
		break;
	}
	if(!student_list[0].rollNum){
		{DPRINTF("[ERROR] Student name %s was not found\n",name);}
	}
	else {while(student_list[i].rollNum){
		Display_StudentData(student_list+i);
		i++;
	}}
}


void delet_student(){

	int rollNum;
	Element_Type student_list[SIZE]={{NULL,NULL,0,0,NULL}};

	Element_Type* ptemp  ;

	DPRINTF("Enter the roll number of the student: ");
	scanf("%d",&rollNum);

	switch(Queue_visit_all(&Queue_student , check_unique,rollNum,NULL,0,&ptemp,student_list)){
	case Queue_null:
		DPRINTF("[ERROR] Students database is empty or not yet initialized\n");
		break;
	}
	if(student_list[0].rollNum){

		Queue_rmNode(&Queue_student , ptemp);
		DPRINTF("[INFO] Roll number %d was deleted successfully\n",rollNum);
	}
	else {DPRINTF("[ERROR] Roll number %d was not found\n",rollNum);}
}

void update_student(){

	int rollNum,choice;
	Element_Type student_list[SIZE]={{NULL,NULL,0,0,NULL}};
	Element_Type* temp;
	DPRINTF("Enter the roll number to update the entry: ");
	scanf("%d",&rollNum);
	switch(Queue_visit_all(&Queue_student , check_unique,rollNum,NULL,0,&temp,student_list)){
	case Queue_null:
		DPRINTF("[ERROR] Students database is empty or not yet initialized\n");
		break;
	}
	if(student_list[0].rollNum){
		student_list[0].rollNum = 0;
		while(choice <= 0 || choice > 5){
			DPRINTF("1.First name\n");
			DPRINTF("2.Last name\n");
			DPRINTF("3.Roll no.\n");
			DPRINTF("4.GPA\n");
			DPRINTF("5.Courses ID\n");
			scanf("%d",&choice);
		}
		switch(choice){
		case 1:
			DPRINTF("Enter new first name: ");
			gets(temp->fname);
			DPRINTF("[INFO] Updated successfully\n");
			break;
		case 2:
			DPRINTF("Enter new last name: ");
			gets(temp->lname);
			DPRINTF("[INFO] Updated successfully\n");
			break;
		case 3:
			DPRINTF("Enter new roll no.: ");
			scanf("%d",&rollNum);
			Queue_visit_all(&Queue_student , check_unique,rollNum,NULL,0,&temp,student_list);
			if(!student_list[0].rollNum){
				temp->rollNum=rollNum;
				DPRINTF("[INFO] Updated successfully\n");
			}else{
				DPRINTF("[ERROR] Roll number %d is already taken\n",temp->rollNum); }
			break;
		case 4:
			DPRINTF("Enter new GPA: ");
			scanf("%f",&temp->gpa);
			DPRINTF("[INFO] Updated successfully\n");
			break;
		case 5:
			DPRINTF("Enter new courses ID: \n");
			int i;
			for(i=0;i<5;i++){
				DPRINTF("Course %d ID: ",i+1);
				scanf("%d",&temp->courseID[i]);
			}

			DPRINTF("[INFO] Updated successfully\n");
			break;
		default:
			DPRINTF("[ERROR] Invalid input\n");
			break;
		}

	}
}
void show_students(){

	Queue_visit_all(&Queue_student , check_unique,0,NULL,0,NULL,NULL);
}
