/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
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

#include "../stm32_F103C6_drivers/inc/stm32f103c6.h"
#include "../stm32_F103C6_drivers/inc/stm32_F103C6_gpio_driver.h"
#include "../HAL/inc/lcd_driver.h"
#include <keypad.h>
#include "../stm32_F103C6_drivers/inc/stm32f103c6_EXTI_driver.h"


uint8_t IRQ_Flag =0;



void EXTI9_callback(void)
{
	IRQ_Flag=1;
	LCD_WRITE_STR(" IRQ9 is happened Omar");
	wait_ms(1000);

}

int main(void)
{
	//Enable clock
	RCC_GPIOA_CLK_EN();
	RCC_GPIOB_CLK_EN();
	RCC_AFIO_CLK_EN();

	//Lcd Init
	LCD_INIT();
	LCD_clear_screen();

	EXTI_PinConfig_t EXTI_Cnfg;
	EXTI_Cnfg.EXTI_PIN = EXTI9PB9;
	EXTI_Cnfg.Trigger_Case = EXTI_Trigger_RISING;
	EXTI_Cnfg.IRQ_EN = EXTI_IRQ_Enable;
	EXTI_Cnfg.p_IRQ_CallBack = EXTI9_callback;
	MCAL_EXTI_GPIO_Init(&EXTI_Cnfg);

	IRQ_Flag=1;

	while(1){
		if(IRQ_Flag)
		{
			LCD_clear_screen();
			IRQ_Flag=0;
		}
	}
}
