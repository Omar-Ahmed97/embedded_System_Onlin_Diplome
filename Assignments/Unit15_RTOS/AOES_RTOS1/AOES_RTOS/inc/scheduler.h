/*
 * scheduler.h
 *
 *  Created on: Mar 15, 2023
 *      Author: Omar
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#include "CortexMX_OS_porting.h"

typedef enum{
	 no_error,
	 Task_Exceeded_StackSize
} MYRTOS_errorID;

typedef struct{
	unsigned int Stack_Size;
	unsigned char priority;
	void (*p_Task_entry)(void);
	unsigned char AutoStart;
	unsigned int _S_PSP_Task;
	unsigned int _E_PSP_Task;
	unsigned int* Current_PSP;
	char TaskName[30];
	enum{
		Suspend,
		Running,
		Waiting,
		Ready
	}TaskState;
	struct {
		enum{
			enable,
			disable
		}Blocking;
		unsigned int Ticks_Count;
	}TimingWaiting;

}Task_ref;


typedef struct{
	unsigned char* Payload;
	unsigned int PayloadSize;
	Task_ref* CurrentTUser;
	Task_ref* NextTUser;
	char MutexName[30];


}Mutex_ref;

#include "AOES_FIFO.h"

void OS_SVC( int * );


MYRTOS_errorID AOES_init();
MYRTOS_errorID  AOES_CreatTask(Task_ref* Tref);
MYRTOS_errorID  AOES_ActivateTask(Task_ref* Tref);
MYRTOS_errorID  AOES_TerminateTask(Task_ref* Tref);
MYRTOS_errorID  AOES_StartOS();
void AOES_TaskWait(Task_ref* Tref ,unsigned int Mills_Count);

void AOES_AcquireMutex(Mutex_ref * Mref,Task_ref* Tref );
void AOES_ReleaseMutex(Mutex_ref * Mref);

#endif /* INC_SCHEDULER_H_ */
