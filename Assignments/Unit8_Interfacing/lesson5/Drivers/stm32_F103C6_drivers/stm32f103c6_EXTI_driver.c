/*
 * stm32f103c6_EXTI_driver.c
 *
 *  Created on: ٠٤‏/٠٧‏/٢٠٢٢
 *      Author: Omar
 */


#include "../stm32_F103C6_drivers/inc/stm32f103c6_EXTI_driver.h"
#include "../stm32_F103C6_drivers/inc/stm32_F103C6_gpio_driver.h"

/*
 * =========================================================================
 * 							Generic Variables
 * ==========================================================================
 */

void(*GP_IRQ_CallBack[15])(void);


/*
 * =========================================================================
 * 							Generic Macros
 * ==========================================================================
 */

#define AFIO_GPIO_EXTI_Mapping(x) 		(	(x==GPIOA)?0:\
											(x==GPIOB)?1:\
											(x==GPIOC)?2:\
											(x==GPIOD)?3:0 )


/*
 * =========================================================================
 * 							Generic Functions
 * ==========================================================================
 */

void Enable_NVIC(uint16_t IRQ)
{
	switch(IRQ)
	{
	case 0:
		NVIC_IRQ6_EXTI0_Enable;
		break;
	case 1:
		NVIC_IRQ7_EXTI1_Enable;
		break;
	case 2:
		NVIC_IRQ8_EXTI2_Enable;
		break;
	case 3:
		NVIC_IRQ9_EXTI3_Enable;
		break;
	case 4:
		NVIC_IRQ10_EXTI4_Enable;
		break;
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
		NVIC_IRQ23_EXTI5_9_Enable;
		break;
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
		NVIC_IRQ40_EXTI10_15_Enable;
		break;

	  }
	}
void Disable_NVIC(uint16_t IRQ)
{
	switch(IRQ)
	{
	case 0:
		NVIC_IRQ6_EXTI0_Disable;
		break;
	case 1:
		NVIC_IRQ7_EXTI1_Disable;
		break;
	case 2:
		NVIC_IRQ8_EXTI2_Disable;
		break;
	case 3:
		NVIC_IRQ9_EXTI3_Disable;
		break;
	case 4:
		NVIC_IRQ10_EXTI4_Disable;
		break;
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
		NVIC_IRQ23_EXTI5_9_Disable;
		break;
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
		NVIC_IRQ40_EXTI10_15_Disable;
		break;

	  }
	}
void Update_EXTI(EXTI_PinConfig_t *EXTI_Config){

	//1- configure GPIO to be alternate functuin input -> Floating Input
	GPIO_PinConfig_t Pin_Cnfg;
	Pin_Cnfg.GPIO_PinNumber = EXTI_Config->EXTI_PIN.GPIO_Pin;
	Pin_Cnfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_Init(EXTI_Config->EXTI_PIN.GPIO_Port, &Pin_Cnfg);

	//================================

	//2-UPDATE AFIO to Route between EXTI Line with Port A,B,C,D
	uint8_t AFIO_ExTICR_index =  	( EXTI_Config->EXTI_PIN.EXTI_InputLineNumber/4 );
	uint8_t AFIO_ExTICR_position =  ( EXTI_Config->EXTI_PIN.EXTI_InputLineNumber %4 ) * 4;

//	000: PA[x] pin
//	001: PB[x] pin
//	002: PC[x] pin
//	003: PD[x] pin

	// clear the four bit
	AFIO->EXTICR[AFIO_ExTICR_index] &= ~(0xf<<AFIO_ExTICR_position);

	AFIO->EXTICR[AFIO_ExTICR_index] |=  ( ((AFIO_GPIO_EXTI_Mapping(EXTI_Config->EXTI_PIN.GPIO_Port)) &0xf) <<AFIO_ExTICR_position);

	//=====================================

	//3- EXTI configuration
	//update rising and fallinf edge

	EXTI->FTSR &= ~( 1<<EXTI_Config->EXTI_PIN.EXTI_InputLineNumber);
	EXTI->RTSR &= ~( 1<<EXTI_Config->EXTI_PIN.EXTI_InputLineNumber);

	if(EXTI_Config->Trigger_Case == EXTI_Trigger_RISING )
	{
		EXTI->RTSR |= ( 1<<EXTI_Config->EXTI_PIN.EXTI_InputLineNumber);

	}else if(EXTI_Config->Trigger_Case == EXTI_Trigger_FALLING )
	{
		EXTI->FTSR |= ( 1<<EXTI_Config->EXTI_PIN.EXTI_InputLineNumber);

	}else if(EXTI_Config->Trigger_Case == EXTI_Trigger_RisingAndFalling )
	{
		EXTI->FTSR |= ( 1<<EXTI_Config->EXTI_PIN.EXTI_InputLineNumber);
		EXTI->RTSR |= ( 1<<EXTI_Config->EXTI_PIN.EXTI_InputLineNumber);
	}

//=========================================================
	//4-Update IRQ Handling CallBack

	GP_IRQ_CallBack[EXTI_Config->EXTI_PIN.EXTI_InputLineNumber] = EXTI_Config->p_IRQ_CallBack;

   //Enable_Disable IRQ EXTI && NVIC
	if(EXTI_Config->IRQ_EN == EXTI_IRQ_Enable)
	{
		EXTI->IMR |=(1<< EXTI_Config->EXTI_PIN.EXTI_InputLineNumber);
		Enable_NVIC(EXTI_Config->EXTI_PIN.EXTI_InputLineNumber);
	}else
	{
		EXTI->IMR &=~(1<< EXTI_Config->EXTI_PIN.EXTI_InputLineNumber);
		Disable_NVIC(EXTI_Config->EXTI_PIN.EXTI_InputLineNumber);

	}

	//
}


/*
 * =========================================================================
 * 							API'S Functions Definitions
 * ==========================================================================
 */


/**================================================================
* @Fn					- MCAL_EXTI_GPIO_Init
* @brief 				- reset EXTI Registers and NVIC correspondin IRQ Mask
* @param [in] 			- none
* @retval 				- none
* Note					- none
*/
/**================================================================*/
void MCAL_EXTI_GPIO_DeInit(){

	EXTI->IMR 	=	0x00000000;
	EXTI->EMR 	= 	0x00000000;
	EXTI->RTSR 	= 	0x00000000;
	EXTI->FTSR 	= 	0x00000000;
	EXTI->SWIER = 	0x00000000;
	EXTI->PR 	= 	0xFFFFFFFF;  //This bit is set when the selected edge event arrives on the external interrupt line. This bit is
								//	cleared by writing a ‘1’ into the bit.

	// Disable EXTI IRQ from NVIC
	 NVIC_IRQ6_EXTI0_Disable  ;
	 NVIC_IRQ7_EXTI1_Disable  ;
	 NVIC_IRQ8_EXTI2_Disable   ;
	 NVIC_IRQ9_EXTI3_Disable    ;
	 NVIC_IRQ10_EXTI4_Disable    ;
	 NVIC_IRQ23_EXTI5_9_Disable   ;
	 NVIC_IRQ40_EXTI10_15_Disable   ;

}

/**================================================================
* @Fn					- MCAL_EXTI_GPIO_Init
* @brief 				- this is used to initialize EXTI from specific Gpio pin and specify MASK/TRIGGER Condition and IRQ Callback
* @param [in] 			- EXTI_Config : set by the refrence @ref EXTI_define  EXTI_Trigger_define and  EXTI_IRQ_define
* @retval 				- none
* Note					- Mandatory to Enable RCC clock for AFIO and the corresponding GPIO
*/
/**================================================================*/
void MCAL_EXTI_GPIO_Init(EXTI_PinConfig_t *EXTI_Config){

	Update_EXTI(EXTI_Config);
}

/**================================================================
* @Fn					- MCAL_EXTI_GPIO_Update
* @brief 				- this is used to update EXTI from specific Gpio pin and specify MASK/TRIGGER Condition and IRQ Callback
* @param [in] 			- EXTI_Config : set by the refrence @ref EXTI_define  EXTI_Trigger_define and  EXTI_IRQ_define
* @retval 				- none
* Note					- Mandatory to Enable RCC clock for AFIO and the corresponding GPIO
*/
/**================================================================*/
void MCAL_EXTI_GPIO_Update(EXTI_PinConfig_t *EXTI_Config){

	Update_EXTI(EXTI_Config);

}

/*
 * =========================================================================
 * 							ISR FUNCTION
 * ==========================================================================
 */

void EXTI0_IRQHandler(void)
{
	// clear Pending register
	EXTI->PR |= 1<<0;
	//CALL IRQ_CALL
	GP_IRQ_CallBack[0]();
	}
void EXTI1_IRQHandler(void)
{
	// clear Pending register
	EXTI->PR |= 1<<1;
	//CALL IRQ_CALL
	GP_IRQ_CallBack[1]();
	}
void EXTI2_IRQHandler(void)
{
	// clear Pending register
	EXTI->PR |= 1<<2;
	//CALL IRQ_CALL
	GP_IRQ_CallBack[2]();
	}
void EXTI3_IRQHandler(void)
{
	// clear Pending register
	EXTI->PR |= 1<<3;
	//CALL IRQ_CALL
	GP_IRQ_CallBack[3]();
	}
void EXTI4_IRQHandler(void)
{
	// clear Pending register
	EXTI->PR |= 1<<4;
	//CALL IRQ_CALL
	GP_IRQ_CallBack[4]();
	}
void EXTI9_5_IRQHandler(void)
{
	if(EXTI->PR & 1<<5 )  { EXTI->PR |= 1<<5;     GP_IRQ_CallBack[5](); }
	if(EXTI->PR & 1<<6 )  { EXTI->PR |= 1<<6;     GP_IRQ_CallBack[6](); }
	if(EXTI->PR & 1<<7 )  { EXTI->PR |= 1<<7;     GP_IRQ_CallBack[7](); }
	if(EXTI->PR & 1<<8 )  { EXTI->PR |= 1<<8;     GP_IRQ_CallBack[8](); }
	if(EXTI->PR & 1<<9 )  { EXTI->PR |= 1<<9;     GP_IRQ_CallBack[9](); }
	}
void EXTI0_15_IRQHandler(void)
{
	if(EXTI->PR & 1<<10 )  { EXTI->PR |= 1<<10;     GP_IRQ_CallBack[10](); }
	if(EXTI->PR & 1<<11 )  { EXTI->PR |= 1<<11;     GP_IRQ_CallBack[11](); }
	if(EXTI->PR & 1<<12 )  { EXTI->PR |= 1<<12;     GP_IRQ_CallBack[12](); }
	if(EXTI->PR & 1<<13 )  { EXTI->PR |= 1<<13;     GP_IRQ_CallBack[13](); }
	if(EXTI->PR & 1<<14 )  { EXTI->PR |= 1<<14;     GP_IRQ_CallBack[14](); }
	if(EXTI->PR & 1<<15 )  { EXTI->PR |= 1<<15;     GP_IRQ_CallBack[15](); }

	}
