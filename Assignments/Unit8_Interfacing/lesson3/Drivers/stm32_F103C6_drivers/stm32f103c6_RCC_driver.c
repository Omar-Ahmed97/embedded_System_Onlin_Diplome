/*
 * stm32f103c6_RCC_driver.c
 *
 *  Created on: ١٤‏/٠٧‏/٢٠٢٢
 *      Author: Omar
 */


#include "../stm32_F103C6_drivers/inc/stm32f103c6_RCC_driver.h"

/*
 * =========================================================================
 * 							Generic Variables
 * ==========================================================================
 */
//Set and cleared by software to control AHB clock division factor.
//0xxx: SYSCLK not divided
//1000: SYSCLK divided by 2
//1001: SYSCLK divided by 4
//1010: SYSCLK divided by 8
//1011: SYSCLK divided by 16
//1100: SYSCLK divided by 64
//1101: SYSCLK divided by 128
//1110: SYSCLK divided by 256
//1111: SYSCLK divided by 512

const uint8_t SYSCLKPrescTable[16U] ={0 ,0, 0, 0, 0,0,0,0, 1,2,3,4,6,7,8,9};

//Set and cleared by software to control the division factor of the APB High speed clock (PCLK2).
//0xx: HCLK not divided
//100: HCLK divided by 2
//101: HCLK divided by 4
//110: HCLK divided by 8
//111: HCLK divided by 16

const uint8_t APBPrescTable[8U] ={0 ,0, 0, 0, 1,2,3,4};

uint32_t MCAL_RCC_GetPCLK1Freq(void){
//	Bits 10:8 PPRE1[2:0]: APB Low-speed prescaler (APB1)
 return	( MCAL_RCC_GetHCLKFreq() >> APBPrescTable[ ( ( RCC->CFGR >>8) & 0b111 )] );

}
uint32_t MCAL_RCC_GetPCLK2Freq(void){
//	Bits 13:11 PPRE2[2:0]: APB high-speed prescaler (APB2)
	 return	( MCAL_RCC_GetHCLKFreq() >> APBPrescTable[ ( ( RCC->CFGR >>11) & 0b111 )] );

}

uint32_t MCAL_RCC_GetHCLKFreq(void){
	//Bits 7:4 HPRE[3:0]: AHB prescaler
	 return	( MCAL_RCC_GetSYSCLKFreq() >> SYSCLKPrescTable[ ( ( RCC->CFGR >>4) & 0xf )] );
}
uint32_t MCAL_RCC_GetSYSCLKFreq(void){

//	Bits 3:2 SWS[1:0]: System clock switch status
	switch((  ( RCC->CFGR >>2) & 0b11  )){

	case 0:
		return HSI_RC_CLK ;
		break;

	case 1:
		//to do //user should specify
		return HSE_CLK ;
		break;
	case 2 :
		//to do need to calculate pll
		return 16000000 ;
		break;
	}
	return HSI_RC_CLK;
}
