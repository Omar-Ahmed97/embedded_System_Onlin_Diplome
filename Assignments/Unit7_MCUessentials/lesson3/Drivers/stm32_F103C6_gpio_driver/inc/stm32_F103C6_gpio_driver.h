/*
 * stm32_F103C6_gpio_driver.h
 *
 *  Created on: Jun 30, 2022
 *      Author: Omar
 */

#ifndef INC_STM32_F103C6_GPIO_DRIVER_H_
#define INC_STM32_F103C6_GPIO_DRIVER_H_

//-----------------------------
//Includes
#include "stm32f103c6.h"
//-----------------------------


//-----------------------------
//User type definitions (structures) Configuration

typedef struct{

	uint16_t GPIO_PinNumber	   	;    	//specifies the Gpio pin to be configured
									// This prameter must be a value of @ref GPIO_PINS_define
	uint8_t GPIO_MODE    	     ;		//specifies the operation mode for the selected pin
									// This prameter must be a value of @ref GPIO_MODE_define
	uint8_t GPIO_Output_Speed    ; //specifies the speed for the selected pin
									// This prameter must be a value of @ref GPIO_SPEED_define

}GPIO_PinConfig_t;


//-----------------------------





//-----------------------------
//Macros Configuration References
//-----------------------------
//@ref GPIO_PINS_define

#define GPIO_PIN_0   								((uint16_t)0x0001)   /* Pin 0 selected */
#define GPIO_PIN_1   								((uint16_t)0x0002)   /* Pin 1 selected */
#define GPIO_PIN_2   								((uint16_t)0x0004)   /* Pin 2 selected */
#define GPIO_PIN_3   								((uint16_t)0x0008)   /* Pin 3 selected */
#define GPIO_PIN_4   								((uint16_t)0x0010)   /* Pin 4 selected */
#define GPIO_PIN_5   								((uint16_t)0x0020)   /* Pin 5 selected */
#define GPIO_PIN_6   								((uint16_t)0x0040)   /* Pin 6 selected */
#define GPIO_PIN_7   								((uint16_t)0x0080)   /* Pin 7 selected */
#define GPIO_PIN_8   								((uint16_t)0x0100)   /* Pin 8 selected */
#define GPIO_PIN_9   								((uint16_t)0x0200)   /* Pin 9 selected */
#define GPIO_PIN_10   								((uint16_t)0x0400)   /* Pin 10 selected */
#define GPIO_PIN_11   								((uint16_t)0x0800)   /* Pin 11 selected */
#define GPIO_PIN_12   								((uint16_t)0x1000)   /* Pin 12 selected */
#define GPIO_PIN_13            					    ((uint16_t)0x2000)  /* Pin 13 selected   */
#define GPIO_PIN_14  								((uint16_t)0x4000)   /* Pin 14 selected */
#define GPIO_PIN_15  								((uint16_t)0x8000)   /* Pin 15 selected */
#define GPIO_PIN_All  								((uint16_t)0xFFFF)   /* ALL PINs selected */

#define GPIO_PIN_MASK 								((uint16_t)0x0000FFFF)   /* PIN mask for test */

//@ref GPIO_MODE_define


//0: Analog mode
//1: Floating input (reset state)
//2: Input with pull-up
//3: pull-down
//4: General purpose output push-pull
//5: General purpose output Open-drain
//6: Alternate function output Push-pull
//7: Alternate function output Open-drain
//8: Alternate function INPUT

#define GPIO_MODE_ANALOG  									((uint8_t)0x0000u)   /* Analog mode */
#define GPIO_MODE_INPUT_FLO   								((uint8_t)0x0001u)   /* Floating input (reset state) */
#define GPIO_MODE_INPUT_PU   								((uint8_t)0x0002u)   /* Input with pull-up */
#define GPIO_MODE_INPUT_PD 									((uint8_t)0x0003u)   /* Input with pull-down */
#define GPIO_MODE_OUTPUT_PP   								((uint8_t)0x0004u)   /* General purpose output push-pull */
#define GPIO_MODE_OUTPUT_OD  								((uint8_t)0x0005u)   /* General purpose output Open-drain */
#define GPIO_MODE_OUTPUT_AF_PP   							((uint8_t)0x0006u)   /* Alternate function output Push-pull */
#define GPIO_MODE_OUTPUT_AF_OD   							((uint8_t)0x0007u)   /* Alternate function output Open-drain */
#define GPIO_MODE_INPUT_AF  								((uint8_t)0x0008u)   /* Alternate function INPUT */


//@ref GPIO_SPEED_define

//1: Output mode, max speed 10 MHz.
//2: Output mode, max speed 2 MHz.
//3: Output mode, max speed 50 MHz


#define GPIO_SPEED_10M  									((uint8_t)0x0001u)   /* Output mode, max speed 10 MHz. */
#define GPIO_SPEED_2M   									((uint8_t)0x0002u)   /* Output mode, max speed 2 MHz */
#define GPIO_SPEED_3M  										((uint8_t)0x0003u)   /* Output mode, max speed 50 MHz*/



//@ref GPIO_PIN_state

#define GPIO_PIN_SET   										((uint8_t)0x0001u)
#define GPIO_PIN_RESET  									((uint8_t)0x0000u)

//@ref GPIO_RETURN_LOCK

#define GPIO_RETURN_LOCK_Enabeld 							((uint8_t)0x0001u)
#define GPIO_RETURN_LOCK_ERROR								((uint8_t)0x0000u)


/*
* ===============================================
* APIs Supported by "MCAL GPIO DRIVER"
* ===============================================
*/

void MCAL_GPIO_Init(GPIO_TypeDef * GPIOx , GPIO_PinConfig_t * PinConfig);
void MCAL_GPIO_DeInit(GPIO_TypeDef * GPIOx );

//Read APIs
uint8_t MCAL_GPIO_ReadPin(GPIO_TypeDef * GPIOx , uint16_t  PinNumber);
uint16_t MCAL_GPIO_ReadPort(GPIO_TypeDef * GPIOx );

//Write APIs
void MCAL_GPIO_WritePin(GPIO_TypeDef * GPIOx ,  uint16_t  PinNumber ,  uint8_t  PinValue);
void MCAL_GPIO_WritePort(GPIO_TypeDef * GPIOx ,  uint16_t  PortValue);

void MCAL_GPIO_TogglePin(GPIO_TypeDef * GPIOx , uint16_t  PinNumber);

uint8_t MCAL_GPIO_LockPin(GPIO_TypeDef * GPIOx , uint16_t  PinNumber);

#endif /* INC_STM32_F103C6_GPIO_DRIVER_H_ */
