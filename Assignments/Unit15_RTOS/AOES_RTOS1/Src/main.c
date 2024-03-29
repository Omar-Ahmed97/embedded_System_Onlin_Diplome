/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#include "core_cm3.h"


#include "scheduler.h"
 Task_ref Task1, Task2,Task3, Task4;
unsigned char Task1_led,Task2_led,Task3_led,Task4_led;
Mutex_ref mutex1;
unsigned char payload[3]={1,2,3};

void task1()
{
	static int count =0;
	while(1){
		Task1_led ^=1;
		count++;
		if(count == 100){
			AOES_AcquireMutex(&mutex1, &Task1);
				AOES_ActivateTask(&Task2);

				}
		if(count == 200){
				count =0;
				AOES_ReleaseMutex(&mutex1);
						}
	//	AOES_TaskWait(&Task1,100);
	}
}

void task2()
{
	static int count =0;
	while(1){

		Task2_led ^=1;
		count++;
		if(count == 100){
			AOES_ActivateTask(&Task4);

		}
		//AOES_TaskWait(&Task2,500);
		if(count == 200){
			AOES_TerminateTask(&Task2);
			count =0;
				}
	}
}
void task3()
{
	while(1){

		Task3_led ^=1;
		AOES_TaskWait(&Task3,500);
	}
}

void task4()
{
	static int count =0;
	while(1){

		Task4_led ^=1;
	//	AOES_TaskWait(&Task4,1000);
		count++;
		if(count == 3){
			AOES_AcquireMutex(&mutex1, &Task4);

				}
		if(count == 200){
			AOES_ReleaseMutex(&mutex1);
			AOES_TerminateTask(&Task4);
			count =0;
		}
	}
}


int main(void)
{
	//MYRTOS_errorID error;
//HW_Init(Initialize clock tree , Reset Controller)

	HW_init();
	AOES_init();

	mutex1.Payload = payload;
	mutex1.PayloadSize = 3;
	strcpy(mutex1.MutexName,"mutex1");

	//Task1
	Task1.Stack_Size = 1024;
	Task1.p_Task_entry = task1;
	Task1.priority = 4;
	strcpy(Task1.TaskName,"task_1");

	//Task2
	Task2.Stack_Size = 1024;
	Task2.p_Task_entry = task2;
	Task2.priority = 3;
	strcpy(Task2.TaskName,"task_2");

	//Task3
//	Task3.Stack_Size = 1024;
//	Task3.p_Task_entry = task3;
//	Task3.priority = 3;
//	strcpy(Task3.TaskName,"task_3");

	//Task4
	Task4.Stack_Size = 1024;
	Task4.p_Task_entry = task4;
	Task4.priority = 1;
	strcpy(Task4.TaskName,"task_4");


	AOES_CreatTask(&Task1);
	AOES_CreatTask(&Task2);
//	AOES_CreatTask(&Task3);
	AOES_CreatTask(&Task4);

	AOES_ActivateTask(&Task1);
//	AOES_ActivateTask(&Task2);
//	AOES_ActivateTask(&Task3);
//	AOES_ActivateTask(&Task4);

	AOES_StartOS();
	while(1){

}
}
