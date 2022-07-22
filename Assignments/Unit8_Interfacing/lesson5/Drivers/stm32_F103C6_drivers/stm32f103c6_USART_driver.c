/*
 * stm32f103c6_USART_driver.c
 *
 *  Created on: ١٤‏/٠٧‏/٢٠٢٢
 *      Author: Omar
 */

#include "../stm32_F103C6_drivers/inc/stm32f103c6_USART_driver.h"


/*
 * =========================================================================
 * 							Generic Variables
 * ==========================================================================
 */

/*
 * =========================================================================
 * 							Generic Macros
 * ==========================================================================
 */


/*
 * =========================================================================
 * 							Generic Functions
 * ==========================================================================
 */
	UART_Config * Global_UART_Config = NULL;
/*
 * =========================================================================
 * 							API'S Functions Definitions
 * ==========================================================================
 */

/**================================================================
* @Fn					- MCAL_UART_Init
* @brief 				- initialize USARTx Registers  correspondin UART_cnfg
* @param [in] 			- USARTx : where x can be (1,2,3,.. depending on device used)
* @param [in] 			- UART_cnfg : UART configuration Specified by the user
* @retval 				- none
* Note					- Now Support ASYNCH mode and Clock 8Mhz
*/
/**================================================================*/

	void MCAL_UART_Init (USART_TypeDef *USARTx, UART_Config* UART_Config)
	{
		Global_UART_Config = UART_Config ;
		uint32_t pclk ,BRR  ;
		//	enable the Clock for given USART peripheral

		if ( USARTx == USART1 )
			RCC_USART1_CLK_EN();

		else if ( USARTx == USART2 )
			RCC_USART2_CLK_EN();

		else if ( USARTx == USART3 )
			RCC_USART3_CLK_EN();



		//Enable USART Module
		//	USART_CR1  Bit 13 UE: USART enable
		USARTx->CR1 |= 1<<13 ;

		//Enable USART Tx and Rx engines according to the USART_Mode configuration item
		//	USART_CR1 Bit 3 TE: Transmitter enable & Bit 2 RE: Receiver enable
		USARTx->CR1 |= UART_Config->USART_Mode ;

		//PAYLOAD Width
		// USARTx->CR1  Bit 12 M: Word length
		USARTx->CR1 |= UART_Config->Payload_Length;

		//Configuration of parity control bit fields
		// USARTx->CR1 	Bit 10 PCE: Parity control enable     Bit 9 PS: Parity selection
		USARTx->CR1 |= UART_Config->Parity ;

		//configure the number of stop bits
		//USART_CR2  Bits 13:12 STOP: STOP bits
		USARTx->CR2 |= UART_Config->StopBits ;


		//USART hardware flow control
		//USART_CR3  Bit 9 CTSE: CTS enable   Bit 8 RTSE: RTS enable
		USARTx->CR3 |= UART_Config->HwFlowCtl ;


		//Configuration of BRR(Baudrate register)
		//PCLK1 for USART2, 3
		//PCLK2 for USART1
		if ( USARTx == USART1 )
		{
			pclk = MCAL_RCC_GetPCLK2Freq();
		}
		else
		{
			pclk = MCAL_RCC_GetPCLK1Freq();
		}

		BRR = UART_BRR_Register(pclk, UART_Config->BaudRate) ;

		USARTx->BRR = BRR ;


		//ENABLE / DISABLE Interrupt
		//USART_CR1
		if (UART_Config->IRQ_Enable  != UART_IRQ_Enable_NONE)
		{
			USARTx->CR1 |= (UART_Config->IRQ_Enable) ;
			//		Enable NVIC For USARTx IRQ
			if ( USARTx == USART1 )
				NVIC_IRQ37_USART1_Enable ;

			else if ( USARTx == USART2 )
				NVIC_IRQ38_USART2_Enable ;

			else if ( USARTx == USART3 )
				NVIC_IRQ39_USART3_Enable ;
		}

	}
/**================================================================
* @Fn					- MCAL_UART_Init
* @brief 				- initialize USARTx Registers  correspondin UART_cnfg
* @param [in] 			- USARTx : where x can be (1,2,3,.. depending on device used)
* @retval 				- none
* Note					- Now Support ASYNCH mode and Clock 8Mhz
*/
/**================================================================*/

void MCAL_UART_DeInit(USART_TypeDef * USARTx){

	if(USARTx == USART1){
		RCC_USART1_Reset();
		NVIC_IRQ37_USART1_Disable;
	}else if(USARTx == USART2){
		RCC_USART2_Reset();
		NVIC_IRQ38_USART2_Disable;
	}else if(USARTx == USART3){

		  RCC_USART3_Reset();
		NVIC_IRQ39_USART3_Disable;
	}
}

/**================================================================
* @Fn					- MCAL_UART_SendData
* @brief 				- initialize USARTx Registers  correspondin UART_cnfg
* @param [in] 			- USARTx : where x can be (1,2,3,.. depending on device used)
* @param [in] 			- pTxBuffer
* @param [in] 			- PollingEn : Enable polling or disabling it
* @retval 				- none
* Note					- shoud initialize UART first
//* 						When transmitting with the parity enabled (PCE bit set to 1 in the USART_CR1 register),
							//the value written in the MSB (bit 7 or bit 8 depending on the data length) has no effect
							//because it is replaced by the parity.
							//When receiving with the parity enabled, the value read in the MSB bit is the received parity bit.
*/
/**================================================================*/

void MCAL_UART_SendData	(USART_TypeDef *USARTx, uint16_t *pTxBuffer,enum Polling_mechanism PollingEn )
{
	if(PollingEn == enable){
		while(!(USARTx->SR & 1<<7));
	}
	//check usart wordlength item for 9 bit or 8 bit

	if(Global_UART_Config->Payload_Length == UART_Payload_Length_9B){
		USARTx->DR = (*pTxBuffer & (uint16_t) 0x01ff);
	}else{
		USARTx->DR = (*pTxBuffer & (uint16_t) 0xff);
	}

}


void MCAL_UART_Wait_TC(USART_TypeDef * USARTx){
	while(!(USARTx->SR & 1<<6));
}


void MCAL_UART_ReceivData(USART_TypeDef * USARTx, uint16_t * pRxBuffer, enum Polling_mechanism  PollingEn){
	//wait until RXNE flag is set in the SR
	if(PollingEn == enable){
			while(!(USARTx->SR & 1<<5));
		}

	//check usart wordlength item for 9 bit or 8 bit

	if(Global_UART_Config->Payload_Length == UART_Payload_Length_9B){

		if(Global_UART_Config->Parity == UART_Parity__NONE){
			//no parity so all 9bits are considered data
			*((uint16_t *)pRxBuffer) = USARTx->DR;
		}else{

			//parity is used so 8 bit will be of user data and 1 for parity
			*((uint16_t *)pRxBuffer) = (USARTx->DR  & (uint8_t)0xff);
		}
	}else{

		if(Global_UART_Config->Parity == UART_Parity__NONE){
					//no parity so all 8bits are considered data
			*((uint16_t *)pRxBuffer) = (USARTx->DR  & (uint8_t)0xff);
				}else{

					//parity is used so 7 bit will be of user data and 1 for parity
					*((uint16_t *)pRxBuffer) = (USARTx->DR  & (uint8_t)0x7f);
				}

	}

}

/**================================================================
* @Fn					- MCAL_UART_GPIO_Set_Pins
* @brief 				- Set recomendeed settings for GPIO pins
* @param [in] 			- USARTx : where x can be (1,2,3,.. depending on device used)
* @retval 				- none
* Note					- Now Support ASYNCH mode and Clock 8Mhz
*/
/**================================================================*/
void MCAL_UART_GPIO_Set_Pins(USART_TypeDef * USARTx){

	GPIO_PinConfig_t pinCnfg;

	if(USARTx == USART1){
		//PA9 TX
		//PA10 RX
		//PA11 CTS
		//PA12 RTS

		//PA9 TX
		pinCnfg.GPIO_PinNumber = GPIO_PIN_9;
		pinCnfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
		pinCnfg.GPIO_Output_Speed= GPIO_SPEED_10M;
		MCAL_GPIO_Init(GPIOA, &pinCnfg);

		//PA10 RX
		pinCnfg.GPIO_PinNumber = GPIO_PIN_10;
		pinCnfg.GPIO_MODE = GPIO_MODE_INPUT_AF;
		MCAL_GPIO_Init(GPIOA, &pinCnfg);

		if(Global_UART_Config->HwFlowCtl == UART_HwFlowCtl_CTS || Global_UART_Config->HwFlowCtl == UART_HwFlowCtl_RTS_CTS){

			//PA11CTS
			pinCnfg.GPIO_PinNumber = GPIO_PIN_11;
			pinCnfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOA, &pinCnfg);

		}
		if(Global_UART_Config->HwFlowCtl == UART_HwFlowCtl_CTS || Global_UART_Config->HwFlowCtl == UART_HwFlowCtl_RTS_CTS){

			//PA12RTS
			pinCnfg.GPIO_PinNumber = GPIO_PIN_12;
			pinCnfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			pinCnfg.GPIO_Output_Speed= GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOA, &pinCnfg);

		}

		}else if(USARTx == USART2){

			//PA2 TX
					//PA3 RX
					//PA0 CTS
					//PA1 RTS

					//PA9 TX
					pinCnfg.GPIO_PinNumber = GPIO_PIN_2;
					pinCnfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_OD;
					pinCnfg.GPIO_Output_Speed= GPIO_SPEED_10M;
					MCAL_GPIO_Init(GPIOA, &pinCnfg);

					//PA10 RX
					pinCnfg.GPIO_PinNumber = GPIO_PIN_3;
					pinCnfg.GPIO_MODE = GPIO_MODE_INPUT_AF;
					MCAL_GPIO_Init(GPIOA, &pinCnfg);

					if(Global_UART_Config->HwFlowCtl == UART_HwFlowCtl_CTS || Global_UART_Config->HwFlowCtl == UART_HwFlowCtl_RTS_CTS){

						//PA11CTS
						pinCnfg.GPIO_PinNumber = GPIO_PIN_0;
						pinCnfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
						MCAL_GPIO_Init(GPIOA, &pinCnfg);

					}
					if(Global_UART_Config->HwFlowCtl == UART_HwFlowCtl_CTS || Global_UART_Config->HwFlowCtl == UART_HwFlowCtl_RTS_CTS){

						//PA12RTS
						pinCnfg.GPIO_PinNumber = GPIO_PIN_1;
						pinCnfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
						pinCnfg.GPIO_Output_Speed= GPIO_SPEED_10M;
						MCAL_GPIO_Init(GPIOA, &pinCnfg);

					}

		}else if(USARTx == USART3){

			//PB10 TX
					//PB11 RX
					//PB13 CTS
					//PB14 RTS

					//PB10 TX
					pinCnfg.GPIO_PinNumber = GPIO_PIN_10;
					pinCnfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_OD;
					pinCnfg.GPIO_Output_Speed= GPIO_SPEED_10M;
					MCAL_GPIO_Init(GPIOB, &pinCnfg);

					//PA10 RX
					pinCnfg.GPIO_PinNumber = GPIO_PIN_11;
					pinCnfg.GPIO_MODE = GPIO_MODE_INPUT_AF;
					MCAL_GPIO_Init(GPIOB, &pinCnfg);

					if(Global_UART_Config->HwFlowCtl == UART_HwFlowCtl_CTS|| Global_UART_Config->HwFlowCtl == UART_HwFlowCtl_RTS_CTS){

						//PA11CTS
						pinCnfg.GPIO_PinNumber = GPIO_PIN_13;
						pinCnfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
						MCAL_GPIO_Init(GPIOB, &pinCnfg);

					}
					if(Global_UART_Config->HwFlowCtl == UART_HwFlowCtl_CTS || Global_UART_Config->HwFlowCtl == UART_HwFlowCtl_RTS_CTS){

						//PA12RTS
						pinCnfg.GPIO_PinNumber = GPIO_PIN_14;
						pinCnfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
						pinCnfg.GPIO_Output_Speed= GPIO_SPEED_10M;
						MCAL_GPIO_Init(GPIOB, &pinCnfg);

					}


		}
}


//ISR

void USART1_IRQHandler(void){

	Global_UART_Config->P_IRQ_CallBack();

}

void USART2_IRQHandler(void){

	Global_UART_Config->P_IRQ_CallBack();

}

void USART3_IRQHandler(void){

	Global_UART_Config->P_IRQ_CallBack();

}
