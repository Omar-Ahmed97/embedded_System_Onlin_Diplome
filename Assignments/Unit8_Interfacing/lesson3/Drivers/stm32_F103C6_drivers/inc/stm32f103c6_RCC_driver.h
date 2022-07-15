/*
 * stm32f103c6_RCC_driver.h
 *
 *  Created on: ١٤‏/٠٧‏/٢٠٢٢
 *      Author: Omar
 */

#ifndef INC_STM32F103C6_RCC_DRIVER_H_
#define INC_STM32F103C6_RCC_DRIVER_H_

//-----------------------------
//Includes
#include "../../stm32_F103C6_drivers/inc/stm32f103c6.h"
#include "../stm32_F103C6_drivers/inc/stm32_F103C6_gpio_driver.h"
//-----------------------------


#define HSI_RC_CLK (uint32_t)(8000000)
#define HSE_CLK (uint32_t)(16000000)


/*
* ===============================================
* APIs Supported by "MCAL RCC DRIVER"
* ===============================================
*/

uint32_t MCAL_RCC_GetPCLK1Freq(void);
uint32_t MCAL_RCC_GetPCLK2Freq(void);

uint32_t MCAL_RCC_GetHCLKFreq(void);
uint32_t MCAL_RCC_GetSYSCLKFreq(void);

#endif /* INC_STM32F103C6_RCC_DRIVER_H_ */
