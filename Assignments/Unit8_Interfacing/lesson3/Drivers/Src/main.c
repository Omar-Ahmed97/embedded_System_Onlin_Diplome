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
#include "../stm32_F103C6_drivers/inc/stm32f103c6_USART_driver.h"

	unsigned char ch;

void clock_init(){

	//Enable clock
	RCC_GPIOA_CLK_EN();
	RCC_GPIOB_CLK_EN();
	RCC_AFIO_CLK_EN();

}

void UART_IRQ_CallBack(){

	MCAL_UART_ReceivData(USART1, &ch, disable);
	MCAL_UART_SendData(USART1, &ch, enable);
}

int main(void)
{
	clock_init();



	UART_Config uartCFG;

	uartCFG.BaudRate = UART_BaudeRate_115200 ;
	uartCFG.HwFlowCtl = UART_HwFlowCtl_NONE;
	uartCFG.IRQ_Enable = UART_IRQ_Enable_RXNE;
	uartCFG.P_IRQ_CallBack = UART_IRQ_CallBack;
	uartCFG.Parity = UART_Parity_NONE;
	uartCFG.PayLoad_Length = UART_PayLoad_Length_8B;
	uartCFG.StopBits = UART_StopBits_1;
	uartCFG.USART_Mode = UART_Mode_TX_RX;


	MCAL_UART_Init(USART1, &uartCFG);
	MCAL_UART_GPIO_Set_Pins(USART1);

	while(1){


	}
}