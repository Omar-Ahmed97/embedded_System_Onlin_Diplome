/*
 * CortexMX_OS_porting.h
 *
 *  Created on: Mar 15, 2023
 *      Author: Omar
 */

#ifndef INC_CORTEXMX_OS_PORTING_H_
#define INC_CORTEXMX_OS_PORTING_H_

#include "ARMCM3.h"
#include "core_cm3.h"
extern int _estack;
extern int _heep;
#define MainStackSize   			3072
#define Switch_TO_priviliged       __asm(" mrs r3, CONTROL  \n \t "\
										"lsr r3,r3, #0x1 \n \t" \
										"lsl r3,r3, #0x1 \n \t" \
										"msr CONTROL , r3")
#define Switch_TO_unpriviliged  	__asm( "mrs r3, CONTROL  \n \t " \
											"Orr r3,r3, #0x01 \n \t"\
											"msr CONTROL , r3")

#define OS_SET_PSP(add)  	    	__asm volatile(" mov r0,%0 \n \t msr psp, r0 " : :"r" (add))
#define OS_GET_PSP(add)  		   __asm volatile(" mrs r0,psp \n \t  mov %0,r0 " : "=r" (add))
#define OS_SWITCH_SP_TO_PSP 	   __asm volatile(" mrs r0,CONTROL \n \t orr r0,r0 , #0x2 \n \t msr CONTROL, r0 " )
#define OS_SWITCH_PSP_TO_SP 	 __asm volatile(" mrs r0,CONTROL \n \t And r0,r0 , #0x5 \n \t msr CONTROL, r0 " )



void trigger_OS_PendSV();
void Start_Ticker();


#endif /* INC_CORTEXMX_OS_PORTING_H_ */
