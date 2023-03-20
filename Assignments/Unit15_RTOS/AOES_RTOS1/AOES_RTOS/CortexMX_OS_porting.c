/*
 * CortexMXOS_porting.c
 *
 *  Created on: Mar 15, 2023
 *      Author: Omar
 */


#include "CortexMX_OS_porting.h"

unsigned char Systick_led;

void HardFault_Handler (void){
	while(1);
}
void	MemManage_Handler(void){
	while(1);
}
void	BusFault_Handler(void){
	while(1);
}
void UsageFault_Handler(void){
	while(1);
}




__attribute((naked)) void SVC_Handler()
{
	__asm("tst lr,#4 \n \t "
			"ITE EQ \n \t"
			"mrseq r0 , MSP \n \t"
			"mrsne r0, PSP \n \t"
			"B OS_SVC"
			);
}



void HW_init(){

	//initialize clock tree 8mhz
	//derease pendsv priority less than systick
	__NVIC_SetPriority(PendSV_IRQn, 15);

}

void trigger_OS_PendSV(){

	SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk ;
}

void Start_Ticker(){

	//8Mhz
	//1count 0.125
	//xcount 1ms
	//x = 1000

	SysTick_Config(8000);

}
void SysTick_Handler(){
	//deterine pcurrent and pnext
	//switch context and restore
	Systick_led ^=1;
	AOES_Update_TaskWitingTime();
	Decide_whatNext();
	trigger_OS_PendSV();
}
