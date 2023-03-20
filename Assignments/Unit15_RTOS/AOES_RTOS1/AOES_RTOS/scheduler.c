/*
 * scheduler.c
 *
 *  Created on: Mar 15, 2023
 *      Author: Omar
 */

#include "scheduler.h"

 struct S_OS_Control{

	Task_ref* OSTasks[100]; //SCH table
	unsigned int _S_MSP_Task;
	unsigned int _E_MSP_Task;
	unsigned int PSP_Task_Locator;
	unsigned int NoOfActiveTasks;
	Task_ref* CurrentTask;
	Task_ref* NextTask;
	enum{
		OS_suspend,
		OS_running
	}OSmodeID;


};

 volatile struct S_OS_Control  OS_Control;

typedef enum{
	SVC_ActivateTask,
	SVC_TerminateTask,
	SVC_STaskWaitingTime,

}SVC_ID;

FIFO_Buf_t Ready_Queue ;
Task_ref* Ready_Queue_FIFO[100];

Task_ref AOES_idleTask;

void AOES_CreatTaskStack(Task_ref* Tref){

	/***
	 * Task_frame
	 * =====
	 * xpsr
	 * pc
	 * lr
	 * r12
	 * r4
	 * r3
	 * r2
	 * r1
	 * r0
	 *
	 * ==========
	 * r5, r6,r7, r8,r9,r10,r11 (Save and restore manual )
	 */


	Tref->Current_PSP = Tref->_S_PSP_Task;

	Tref->Current_PSP-- ;

	 *(Tref->Current_PSP) = 0x1000000;

	 Tref->Current_PSP--;
	 *(Tref->Current_PSP) = (unsigned int)(Tref->p_Task_entry);

	 Tref->Current_PSP--;
	 *(Tref->Current_PSP) = (unsigned int)(0xffffffED);

	 for(int j =0 ; j < 13; j++){
		 Tref->Current_PSP--;
	     *(Tref->Current_PSP) = (unsigned int)(0x00);
	 }

	 Tref->_S_PSP_Task =  Tref->Current_PSP ;

}
void bubbleSort(){
	unsigned int i,j,n;
	Task_ref * temp;
	n = OS_Control.NoOfActiveTasks;
	for(i=0; i < n-1 ; i++)
	{
		for(j=0; j < n-1-i ; j++){
			if(OS_Control.OSTasks[j]->priority > OS_Control.OSTasks[j+1]->priority){
				temp = OS_Control.OSTasks[j];
				OS_Control.OSTasks[j] = OS_Control.OSTasks[j+1];
				OS_Control.OSTasks[j+1] = temp;
			}
		}
	}
}
//handler
void AOES_Update_SchedulerTable(){

	Task_ref* temp = NULL;
	Task_ref* pTask = OS_Control.OSTasks[0];
	Task_ref* pNextTask;
	int i = 0;

	//buble sort based on priority
	bubbleSort();
	//free ready queue
	while(FIFO_dequeue(&Ready_Queue, &temp ) != FIFO_EMPTY ){
		if(temp->TaskState != Suspend)
		temp->TaskState = Waiting;
	}

	//update ready queue
	while( i < OS_Control.NoOfActiveTasks ){
	    pTask = OS_Control.OSTasks[i];
		pNextTask = OS_Control.OSTasks[i+1];

		if(pTask->TaskState != Suspend){

			FIFO_enqueue(&Ready_Queue, pTask);
			pTask->TaskState = Ready;

			if(pTask->priority == pNextTask->priority)
				{
				i++;
				continue;
				}

		}

		if(pTask->priority == pNextTask->priority)
				{
						i++;
						continue;
				}
		else if(Ready_Queue.counter !=0 )
			break;
		else i++;


	}

	

}

//

void Decide_whatNext(){


	if(  Ready_Queue.counter == 0 ){
		OS_Control.NextTask = OS_Control.CurrentTask;
	}
	else
	{
		FIFO_dequeue(&Ready_Queue, &OS_Control.NextTask);
		OS_Control.NextTask->TaskState = Running;
	if(OS_Control.CurrentTask->TaskState != Suspend &&  OS_Control.CurrentTask->priority == OS_Control.NextTask->priority)
	{
		FIFO_enqueue(&Ready_Queue, OS_Control.CurrentTask);
		OS_Control.CurrentTask->TaskState = Ready;
	}

	}


}
//handler

void OS_SVC( int * StackFramePointer){

	//r0,r1,r2,r3,r12,lr,pc,xpsr

	volatile unsigned char SVC_num;


	SVC_num =  *( (unsigned char *)(((unsigned char *)StackFramePointer[6])-2) );


	switch (SVC_num){

	case 0:
			AOES_Update_SchedulerTable();
			if(OS_Control.OSmodeID == OS_running)
			{
				if(strcmp(OS_Control.CurrentTask->TaskName , "idleTask") != 0 ){

					Decide_whatNext();

					//Switch context / restore
					trigger_OS_PendSV();
				}
			}


			break;
	case 1:
		AOES_Update_SchedulerTable();
					if(OS_Control.OSmodeID == OS_running)
					{
						if(strcmp(OS_Control.CurrentTask->TaskName , "idleTask") != 0 ){

							Decide_whatNext();

							//Switch context / restore
							trigger_OS_PendSV();
						}
					}


			break;
	case 2:
		AOES_Update_SchedulerTable();
			break;

		}


}

__attribute((naked)) void PendSV_Handler(){

	/*** save context of current task ***/

	//get the current psp
	OS_GET_PSP(OS_Control.CurrentTask->Current_PSP);
	//use current psp to store r4_>11
	OS_Control.CurrentTask->Current_PSP--;
	__asm volatile( "mov %0,r4" :"=r" (*(OS_Control.CurrentTask->Current_PSP)) );
	OS_Control.CurrentTask->Current_PSP--;
	__asm volatile( "mov %0,r5" :"=r" (*(OS_Control.CurrentTask->Current_PSP)) );
	OS_Control.CurrentTask->Current_PSP--;
	__asm volatile( "mov %0,r6" :"=r" (*(OS_Control.CurrentTask->Current_PSP)) );
	OS_Control.CurrentTask->Current_PSP--;
	__asm volatile( "mov %0,r7" :"=r" (*(OS_Control.CurrentTask->Current_PSP)) );
	OS_Control.CurrentTask->Current_PSP--;
	__asm volatile( "mov %0,r8" :"=r" (*(OS_Control.CurrentTask->Current_PSP)) );
	OS_Control.CurrentTask->Current_PSP--;
	__asm volatile( "mov %0,r9" :"=r" (*(OS_Control.CurrentTask->Current_PSP)) );
	OS_Control.CurrentTask->Current_PSP--;
	__asm volatile( "mov %0,r10" :"=r" (*(OS_Control.CurrentTask->Current_PSP)) );
	OS_Control.CurrentTask->Current_PSP--;
	__asm volatile( "mov %0,r11" :"=r" (*(OS_Control.CurrentTask->Current_PSP)) );

	// save current value of psp
	OS_SET_PSP(OS_Control.CurrentTask->Current_PSP);


	/***restor contents of next task ***/
if(OS_Control.NextTask != NULL){
	OS_Control.CurrentTask = OS_Control.NextTask;
	OS_Control.NextTask = NULL;
}

	__asm volatile( "mov r11,%0" : : "r" (*(OS_Control.CurrentTask->Current_PSP)) );
	OS_Control.CurrentTask->Current_PSP++;
	__asm volatile( "mov r10,%0" : : "r" (*(OS_Control.CurrentTask->Current_PSP)) );
	OS_Control.CurrentTask->Current_PSP++;
	__asm volatile( "mov r9,%0" : : "r" (*(OS_Control.CurrentTask->Current_PSP)) );
	OS_Control.CurrentTask->Current_PSP++;
	__asm volatile( "mov r8,%0" : : "r" (*(OS_Control.CurrentTask->Current_PSP)) );
	OS_Control.CurrentTask->Current_PSP++;
	__asm volatile( "mov r7,%0" : : "r" (*(OS_Control.CurrentTask->Current_PSP)) );
	OS_Control.CurrentTask->Current_PSP++;
	__asm volatile( "mov r6,%0" : : "r" (*(OS_Control.CurrentTask->Current_PSP)) );
	OS_Control.CurrentTask->Current_PSP++;
	__asm volatile( "mov r5,%0" : : "r" (*(OS_Control.CurrentTask->Current_PSP)) );
	OS_Control.CurrentTask->Current_PSP++;
	__asm volatile( "mov r4,%0" : : "r" (*(OS_Control.CurrentTask->Current_PSP)) );
	OS_Control.CurrentTask->Current_PSP++;

	// save current value of psp
	OS_SET_PSP(OS_Control.CurrentTask->Current_PSP);
	__asm volatile("BX LR");

}



void AOES_Creat_MainStack(){
	OS_Control._S_MSP_Task = &_estack;
	OS_Control._E_MSP_Task = OS_Control._S_MSP_Task - MainStackSize;
	//Aligned 8 Bytes spaces between main task and psp task
	OS_Control.PSP_Task_Locator = OS_Control._E_MSP_Task - 8;
}

unsigned char idleTaskLED;
void AOES_IdleTask(){
	while(1)
	{
		idleTaskLED ^=1;
		__asm("wfe");
	}
}

MYRTOS_errorID AOES_init(){
	MYRTOS_errorID error = no_error;
	//update os mode (OSsuspend)
	OS_Control.OSmodeID = OS_suspend;
	OS_Control.NoOfActiveTasks = 0;

	//specify the main stack for os
	AOES_Creat_MainStack();

	//create os ready queue
	FIFO_init(&Ready_Queue, Ready_Queue_FIFO, 100);

	//configure idle task

	strcpy(AOES_idleTask.TaskName,"idleTask");
	AOES_idleTask.priority = 255;
	AOES_idleTask.p_Task_entry = AOES_IdleTask ;
	AOES_idleTask.Stack_Size = 300;
	AOES_CreatTask(&AOES_idleTask);
	AOES_idleTask.TaskState = Suspend;
	AOES_idleTask.TimingWaiting.Blocking = disable;

	//AOES_ActivateTask(&AOES_idleTask);
	return error;
}



MYRTOS_errorID  AOES_CreatTask(Task_ref* Tref){
	 MYRTOS_errorID error = no_error;

	// static int index =0;
	 //check task size exceed psp stack
	 //creat its own psp stack
	 Tref->_S_PSP_Task = OS_Control.PSP_Task_Locator;
	 Tref->_E_PSP_Task = Tref->_S_PSP_Task - Tref->Stack_Size;

	// if(Tref->_E_PSP_Task < &(_heep))
//		 return Task_Exceeded_StackSize;

	 //Aliign 8
	 OS_Control.PSP_Task_Locator = Tref->_E_PSP_Task -8 ;

	 OS_Control.OSTasks[OS_Control.NoOfActiveTasks++] = Tref;
	 //Initialize PSP STACK
	 AOES_CreatTaskStack(Tref);

	 //Task State Update -> suspend mode

	 Tref->TaskState = Suspend;
	 Tref->TimingWaiting.Blocking = disable ;

	return error;
}

void AOES_SVC_Set(SVC_ID id){

	switch(id){
	case SVC_ActivateTask:
		__asm volatile("svc #0x00");
		break;
	case SVC_TerminateTask:
		__asm("svc #0x01");
			break;
	case SVC_STaskWaitingTime:
		__asm("svc #0x02");
			break;
	}
}
MYRTOS_errorID  AOES_ActivateTask(Task_ref* Tref){
	 MYRTOS_errorID error = no_error;

	 Tref->TaskState = Waiting;


	AOES_SVC_Set(SVC_ActivateTask);
		return error;
	}

MYRTOS_errorID  AOES_TerminateTask(Task_ref* Tref){
	 MYRTOS_errorID error = no_error;

	 Tref->TaskState = Suspend;
	 AOES_SVC_Set(SVC_TerminateTask);
		return error;
	}
void AOES_TaskWait(Task_ref* Tref ,unsigned int Mills_Count){
	Tref->TimingWaiting.Blocking = enable;
	Tref->TimingWaiting.Ticks_Count = Mills_Count;
	Tref->TaskState = Suspend;
	AOES_TerminateTask( Tref);

}

MYRTOS_errorID  AOES_StartOS(){

	OS_Control.OSmodeID = OS_running;
	//set Default current task
	OS_Control.CurrentTask = &AOES_idleTask;
	//Activate idle task
	AOES_ActivateTask(&AOES_idleTask);


	Start_Ticker();
	OS_SET_PSP(OS_Control.CurrentTask->Current_PSP);

	OS_SWITCH_SP_TO_PSP ;
	Switch_TO_unpriviliged ;
	AOES_idleTask.p_Task_entry();



}

void AOES_Update_TaskWitingTime(){
	volatile int i = 0;
	int n;
	for( i=0 ; i < OS_Control.NoOfActiveTasks ; i++){
		if(OS_Control.OSTasks[i]->TaskState == Suspend)
		{
			if(OS_Control.OSTasks[i]->TimingWaiting.Blocking == enable)
			{
				OS_Control.OSTasks[i]->TimingWaiting.Ticks_Count--;
				if(OS_Control.OSTasks[i]->TimingWaiting.Ticks_Count == 0){
					OS_Control.OSTasks[i]->TimingWaiting.Blocking = disable;
					OS_Control.OSTasks[i]->TaskState = Waiting;
					AOES_SVC_Set(SVC_STaskWaitingTime );
				}
			}
		}
	}
}




void AOES_AcquireMutex(Mutex_ref * Mref,Task_ref* Tref ){
	if(Mref->CurrentTUser == NULL)
	{
		Mref->CurrentTUser = Tref;
	}else
	{
		if(Mref->NextTUser == NULL)
		{
			Mref->NextTUser = Tref;
			Tref->TaskState = Suspend;
			AOES_SVC_Set(SVC_TerminateTask);
		}
	}
}
void AOES_ReleaseMutex(Mutex_ref * Mref){
	if(Mref->CurrentTUser != NULL)
		{
			Mref->CurrentTUser = Mref->NextTUser;
			Mref->NextTUser = NULL;
			Mref->CurrentTUser->TaskState = Waiting;
			AOES_SVC_Set(SVC_ActivateTask);

		}
}
