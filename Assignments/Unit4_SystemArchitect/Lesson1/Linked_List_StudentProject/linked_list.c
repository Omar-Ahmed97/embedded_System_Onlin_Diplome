/*
 * linked_list.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Omar
 */

#include "linked_list.h"


struct SStudent* gpFirstStudent=NULL;


void add_student()
{

	struct SStudent* pNewStudent ;
	struct SStudent* pLastStudent ;
	char temp_text[40];
	//check the list is empty

	if(gpFirstStudent == NULL)
	{
		pNewStudent =(struct SStudent*) malloc(sizeof(struct SStudent));
		//assign it to gpf
		gpFirstStudent = pNewStudent;
	}else // list contain record
	{
		//navigate untill reach last node
		pLastStudent = gpFirstStudent;
		while( pLastStudent->PNextStudent )
			pLastStudent = pLastStudent->PNextStudent ;

		//create new record
		pNewStudent =(struct SStudent*) malloc(sizeof(struct SStudent));
		pLastStudent->PNextStudent  = pNewStudent;

	}
	//fill new record
	Dprintf("Enter the ID\n");
	gets(temp_text);
	pNewStudent->student.ID = atoi(temp_text);



	Dprintf("Enter student full name\n");
	gets(pNewStudent->student.name);

	Dprintf("Enter the student height");
	gets(temp_text);
	pNewStudent->student.height = atof(temp_text);

	//set the next pointer new_student null
	pNewStudent->PNextStudent = NULL;
}

int delete_student()
{

	char temp_text[40];
	unsigned int selcted_id;
	//get the selected id
	Dprintf("\n Enter the student id to be deleted ::");
	gets(temp_text);
	selcted_id = atoi(temp_text);

	// list is not empty!!!

	if(gpFirstStudent)
	{
		struct SStudent* pSelectedStudent = gpFirstStudent;
		struct SStudent* pPreviousStudent = NULL;

		//loop on all records
		while(pSelectedStudent)
		{
			// copare each node with selected id
			if(pSelectedStudent->student.ID == selcted_id)
			{
				if(pPreviousStudent) // the first node is not selected
				{
					pPreviousStudent->PNextStudent= pSelectedStudent->PNextStudent;


				}else{ //1st student == ID
					gpFirstStudent = pSelectedStudent->PNextStudent;

				}
				free(pSelectedStudent);
				return 1;
			}

			//travers the list
			pPreviousStudent =  pSelectedStudent;
			pSelectedStudent = pSelectedStudent->PNextStudent;


		}
	}
	Dprintf("\n cannot find student ID.");
    return 0;
}

void getNth(int index)
{
	struct SStudent* pCurrentStudent = gpFirstStudent;
		int count =1;
		if(!pCurrentStudent)
		{
			Dprintf("\n Empty List \n");
		}else{

			while(pCurrentStudent)
			{
				if(count == index)
				{
				Dprintf("\n record number %d",count+1);
				Dprintf("\n \t ID : %d",pCurrentStudent->student.ID);
				Dprintf("\n \t Name  %s",pCurrentStudent->student.name);
				Dprintf("\n \t height  %f",pCurrentStudent->student.height);
				}

				pCurrentStudent = pCurrentStudent->PNextStudent;
				count++;
			}
		}


}


void view_student()
{
	struct SStudent* pCurrentStudent = gpFirstStudent;
	int count =0;
	if(!pCurrentStudent)
	{
		Dprintf("\n Empty List \n");
	}else{

		while(pCurrentStudent)
		{
			Dprintf("\n record number %d",count+1);
			Dprintf("\n \t ID : %d",pCurrentStudent->student.ID);
			Dprintf("\n \t Name  %s",pCurrentStudent->student.name);
			Dprintf("\n \t height  %f",pCurrentStudent->student.height);

			pCurrentStudent = pCurrentStudent->PNextStudent;
			count++;
		}
	}


}

void deleteAll()
{


	struct SStudent* pCurrentStudent = gpFirstStudent;

	if(pCurrentStudent)
	{
		Dprintf("\n Empty List \n");
	}else{

		while(pCurrentStudent)
		{
			pCurrentStudent = pCurrentStudent->PNextStudent;
			free(gpFirstStudent);
			gpFirstStudent = pCurrentStudent;
		}
	}


}

int printNumEle_rec(struct SStudent *head)
{
	if(!head)
		return 0;
	else return 1+printNumEle_rec(head->PNextStudent);
}

void printNumEle()
{
	int count;
	count = printNumEle_rec(gpFirstStudent);
	printf("\nnumber of elements = %d",count);
}

void findIndexBackward(int index)
{
	struct SStudent* pMainStudent = gpFirstStudent;
	struct SStudent* pRefStudent = gpFirstStudent;
		int count =1;

		if(!pMainStudent)
		{
			Dprintf("\n Empty List \n");
		}else{

			while(count != index){
				 pRefStudent =  pRefStudent->PNextStudent;
				 count++;
			}

			while(pRefStudent->PNextStudent)
			{
				 pRefStudent =  pRefStudent->PNextStudent;
				 pMainStudent =  pMainStudent->PNextStudent;

			}

			Dprintf("\n \t ID : %d",pMainStudent->student.ID);
			Dprintf("\n \t Name  %s",pMainStudent->student.name);
			Dprintf("\n \t height  %f",pMainStudent->student.height);



		}

}

void findMiddle()
{
	struct SStudent* pfastStudent = gpFirstStudent;
	struct SStudent* pslowStudent = gpFirstStudent;


		if(!pslowStudent)
		{
			Dprintf("\n Empty List \n");
		}else{



			while(pfastStudent->PNextStudent)
			{
				pfastStudent =  pfastStudent->PNextStudent->PNextStudent;
				pslowStudent =  pslowStudent->PNextStudent;
				if(!pfastStudent)
				{

					break;
				}


			}

			Dprintf("\n \t ID : %d",pslowStudent->student.ID);
			Dprintf("\n \t Name  %s",pslowStudent->student.name);
			Dprintf("\n \t height  %f",pslowStudent->student.height);



		}

}
void reversNodes()
{
	struct SStudent* pCurrentStudent = gpFirstStudent;
	struct SStudent* pnextStudent = gpFirstStudent;
	struct SStudent* pPrevStudent = NULL;

	while(pCurrentStudent)
	{
		pnextStudent = pCurrentStudent->PNextStudent;
		pCurrentStudent->PNextStudent = pPrevStudent;
		pPrevStudent = pCurrentStudent;
		pCurrentStudent= pnextStudent;
	}

	gpFirstStudent = pPrevStudent;

}
