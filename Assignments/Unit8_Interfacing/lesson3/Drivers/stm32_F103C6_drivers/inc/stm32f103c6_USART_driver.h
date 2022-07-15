/*
 * stm32f103c6_USART_driver.h
 *
 *  Created on: ١٤‏/٠٧‏/٢٠٢٢
 *      Author: Omar
 */

#ifndef INC_STM32F103C6_USART_DRIVER_H_
#define INC_STM32F103C6_USART_DRIVER_H_

//-----------------------------
//Includes
#include "../../stm32_F103C6_drivers/inc/stm32f103c6.h"
#include "../stm32_F103C6_drivers/inc/stm32_F103C6_gpio_driver.h"
#include "../stm32_F103C6_drivers/inc/stm32f103c6_RCC_driver.h"

//-----------------------------


//-----------------------------
//User type definitions (structures) Configuration
//-----------------------------

typedef struct{
	uint8_t USART_Mode ;  //Specify tx/rx Enable / disable
						// this pramter must be specified @ref UART_Mode_define
	uint8_t BaudRate;  //Specify USART Baud Rate
							// this pramter must be specified @ref UART_BaudRate_define
	uint8_t PayLoad_Length ; //Specify USART PayLoad_Length
								// this pramter must be specified @ref PayLoad_Length_define
	uint8_t Parity ;		 //Specify USART parity
									// this pramter must be specified @ref Usart_Parity_define
	uint8_t StopBits ;		 //Specify USART StopBits
										// this pramter must be specified @ref Usart_StopBits_define

	uint8_t HwFlowCtl ;		 //Specify USART HwFlowCtl
										// this pramter must be specified @ref Usart_HwFlowCtl_define
	uint8_t IRQ_Enable ;		 //Enable interrupt for transmitter and reciever
											// this pramter must be specified @ref Usart_IRQ_Enable_define

	void (*P_IRQ_CallBack)(void);	//set the c function which will be called once the IRQ happen

}UART_Config;

//-----------------------------
//Macros Configuration References
//-----------------------------

// @ref UART_Mode_define

#define UART_Mode_RX           		(uint32_t)(1<<2)  //Bit2  Reciever Enable
#define UART_Mode_TX				(uint32_t)(1<<3)  //Bit3 TE enable
#define UART_Mode_TX_RX				(uint32_t)( (1<<3)|(1<<2) )  //Bit2  Reciever Enable   //Bit3 TE enable


//@ref UART_BaudRate_define
#define UART_BaudeRate_2400			2400
#define UART_BaudeRate_9600			9600
#define UART_BaudeRate_19200		19200
#define UART_BaudeRate_57600			57600
#define UART_BaudeRate_115200			115200
#define UART_BaudeRate_230400			230400
#define UART_BaudeRate_460800			460800
#define UART_BaudeRate_921600			921600
#define UART_BaudeRate_2250000			2250000
#define UART_BaudeRate_4500000			4500000


//@ref PayLoad_Length_define
#define UART_PayLoad_Length_8B		(uint32_t)(0)//0: 1 Start bit, 8 Data bits, n Stop bit
#define UART_PayLoad_Length_9B		(uint32_t)(1<<12)//1: 1 Start bit, 9 Data bits, n Stop bit

//@ref Usart_Parity_define
#define UART_Parity_NONE             (uint32_t)(0)
#define UART_Parity_EVEN             (uint32_t)(1<<10)
#define UART_Parity_ODD             (uint32_t)(1<<10 | 1<<9)


//@ref Usart_StopBits_define
#define UART_StopBits_1				(uint32_t)(0)
#define UART_StopBits_half				(uint32_t)(1<<12)
#define UART_StopBits_1_half				(uint32_t)(1<<13 | 1<<12)
#define UART_StopBits_2				(uint32_t)(1<<13)

//@ref Usart_HwFlowCtl_define

#define UART_HwFlowCtl_NONE			(uint32_t)(0)
#define UART_HwFlowCtl_RTS				(uint32_t)(1<<8)
#define UART_HwFlowCtl_1_RTS_CTS				(uint32_t)(1<<9 | 1<<8)
#define UART_HwFlowCtl_CTS				(uint32_t)(1<<9)

//@ref Usart_IRQ_Enable_define
#define UART_IRQ_Enable_NONE			(uint32_t)(0)
#define UART_IRQ_Enable_TXE			(uint32_t)(1<<7)
#define UART_IRQ_Enable_TC			(uint32_t)(1<<6)
#define UART_IRQ_Enable_RXNE			(uint32_t)(1<<5)
#define UART_IRQ_Enable_PE			(uint32_t)(1<<8)

//Baud Rate calculation
//USARTDIV = fclk / (16 * BaudRate)
//USARTDIV_MUL100 = 25 * fclk / (4 * BaudRate)
//DIV_Mantissa_MUL100 = Integer part of USARTDIV_MUL100 * 100
//DIV_Mantissa = Integer part of USARTDIV
//DIV_Fraction = ((USARTDIV_MUL100 - DIV_Mantissa_MUL100 )*16) / 100

#define USARTDIV(_pclk_,_BAUD_)					(uint32_t)(_pclk_ / (16 * _BAUD_))
#define USARTDIV_MUL100(_pclk_,_BAUD_)			(uint32_t)(25 * _pclk_ / (4 * _BAUD_))
#define DIV_Mantissa_MUL100(_pclk_,_BAUD_)					(uint32_t) (USARTDIV(_pclk_,_BAUD_)	* 100)
#define DIV_Mantissa(_pclk_,_BAUD_)							(uint32_t) (USARTDIV(_pclk_,_BAUD_)	)
#define DIV_Fraction(_pclk_,_BAUD_)							(uint32_t) (((USARTDIV_MUL100(_pclk_,_BAUD_) - DIV_Mantissa_MUL100(_pclk_,_BAUD_) )*16) / 100	)
#define UART_BRR_Register(_pclk_,_BAUD_)					((DIV_Mantissa(_pclk_,_BAUD_)) << 4) | ( (DIV_Fraction(_pclk_,_BAUD_)) & 0xf)
enum Polling_mechanism{
	enable ,
	disable
};

/*
* ===============================================
* APIs Supported by "MCAL USART DRIVER"
* ===============================================
*/

void MCAL_UART_Init(USART_TypeDef * USARTx, UART_Config * UART_cnfg);
void MCAL_UART_DeInit(USART_TypeDef * USARTx);
void MCAL_UART_GPIO_Set_Pins(USART_TypeDef * USARTx);
void MCAL_UART_SendData(USART_TypeDef * USARTx, uint16_t * pTxBuffer, enum Polling_mechanism  PollingEn);
void MCAL_UART_ReceivData(USART_TypeDef * USARTx, uint16_t * pRxBuffer, enum Polling_mechanism  PollingEn);
void MCAL_UART_Wait_TC(USART_TypeDef * USARTx);



#endif /* INC_STM32F103C6_USART_DRIVER_H_ */
