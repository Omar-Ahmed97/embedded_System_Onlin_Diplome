/*
 * stm32f103c6_SPI_driver.h
 *
 *  Created on: ٢١‏/٠٧‏/٢٠٢٢
 *      Author: Omar
 */

#ifndef INC_STM32F103C6_SPI_DRIVER_H_
#define INC_STM32F103C6_SPI_DRIVER_H_

//-----------------------------
//Includes
#include "../../stm32_F103C6_drivers/inc/stm32f103c6.h"
#include "../stm32_F103C6_drivers/inc/stm32_F103C6_gpio_driver.h"
#include "../stm32_F103C6_drivers/inc/stm32f103c6_RCC_driver.h"

//-----------------------------

//-----------------------------
//User type definitions (structures) Configuration
//-----------------------------
struct S_IRQ_SRC
{
	uint8_t TXE:1;   //tx buffer empty interrupt
	uint8_t RXNE:1;   //RX buffer not empty interrupt
	uint8_t ERRI:1;   //ERROR interrupt
	uint8_t reserved:5;

};
typedef struct
{
	uint16_t Device_Mode;     		 	 //Specify	the SPI operating mode
										// this pramter must be specified @ref Device_Mode_define

	uint16_t Communication_Mode;	 	//Specify the SPI bidirectional mode state
										// this pramter must be specified @ref Communication_Mode_define

	uint16_t Frame_Format; 				//Specify LSB or MSB transmit first
										// this pramter must be specified  @ref Frame_Format_define

	uint16_t DataSize; 					//Specify SPI Data Size ( 8 or 16 )
										// this pramter must be specified @ref DataSize_define

	uint16_t CLKPolarity; 				//Specify Clock Polarity idle state (HIGH or Low )
										// this pramter must be specified @ref CLKPolarity_define

	uint16_t CLKPhase; 					//Specify Clock Phase start sampling at ( first edge or second edge)
										// this pramter must be specified@ref CLKPhase_define

	uint16_t NSS; 						//Specify whether the NSS pin signal is manged by ( hardwre or software using SSI bit)
										// this pramter must be specified @ref NSS_define

	uint16_t BaudRate_Prescaler;		/* Specifies The Baud Rate Prescaler value which will be used to configure
											the transmit and recieve SCK clock.
											this pramter can be value @ref BaudRate_Prescaler_define
											@note the communication clock is specified by the master cloch
											 the slave clock dont need tb be set */
										//take care yoh hve to econfigure RCC to enter the correct clock to APB2 >> SPI1
	uint16_t IRQ_Enable ;		 //Enable interrupt for transmitter and reciever
											// this pramter must be specified @ref SPI_IRQ_Enable_define

	void (*P_IRQ_CallBack)(struct S_IRQ_SRC irq_src);	//set the c function which will be called once the IRQ happen


}SPI_Config;


//-----------------------------
//Macros Configuration References
//-----------------------------

//@ref Device_Mode_define
//CR1 Bit 2 MSTR: Master selection
//0: Slave configuration
//1: Master configuration
#define SPI_Device_Mode_SLAVE						(0X00000000U)
#define SPI_Device_Mode_MASTER						(0X1U<<2)


//@ref Communication_Mode_define
#define SPI_Direction_2LINE							(0X00000000U)
#define SPI_Direction_2LINE_RXONLY					(0X1U<<10)   			//CR1 BIT10 RXONLY : Recieve only
#define SPI_Direction_1LINE_recieve_only			(0X1U<<15)				//CR1 BIT 15 BIDIMODE: Bidirectional data mode enable
#define SPI_Direction_2LINE_transmit_only			(0X1U<<15 | 0x1U<<14)	//CR1 BIT 15 BIDIMODE: Bidirectional data mode enable && Bit 14 BIDIOE: Output enable in bidirectional mode

//@ref DataSize_define

//DFF: Data frame format
//0: 8-bit data frame format is selected for transmission/reception
//1: 16-bit data frame format is selected for transmission/reception

#define SPI_DataSize_8BIT						(0X00000000U)
#define SPI_DataSize_16BIT						(0X1U<<11)		//CR1 BIT11 Data Frame Format

//@ref Frame_Format_define

//LSBFIRST: Frame format
//0: MSB transmitted first
//1: LSB transmitted first

#define SPI_Frame_Format_MSBfirst						(0X00000000U)
#define SPI_Frame_Format_LSBfirst						(0X1U<<7)		//CR1 BIT7 LSBFIRST

//@ref CLKPolarity_define

//Bit1 CPOL: Clock polarity
//0: CK to 0 when idle
//1: CK to 1 when idle

#define SPI_CLKPolarity_LOW									(0X00000000U)
#define SPI_CLKPolarity_HIGH								(0X1U<<1)		//CR1 BIT1 CPOL


//@ref CLKPhase_define
//CPHA: Clock phase
//0: The first clock transition is the first data capture edge
//1: The second clock transition is the first data capture edge

#define SPI_CLKPhase_firstEdge									(0X00000000U)
#define SPI_CLKPhase_secondEdge									(0X1U<<0)		//CR1 BIT0 CPHA


//@ref NSS_define
//Hardware
//Bit 2 SSOE: SS output enable
//0: SS output is disabled in master mode and the cell can work in multimaster configuration
//1: SS output is enabled in master mode and when the cell is enabled. The cell cannot work
//in a multimaster environment.
#define SPI_NSS_Hard_Slave													(0X00000000U)
#define SPI_NSS_Hard_Master_MultiMaster										~(0X1U<<2) //CR2	Bit 2
#define SPI_NSS_Hard_Master_NotMultiMaster										(0X1U<<2) //CR2	Bit 2

//Software (master or slave)

//Bit 9 SSM: Software slave management
//When the SSM bit is set, the NSS pin input is replaced with the value from the SSI bit.
//0: Software slave management disabled
//1: Software slave management enabled
#define SPI_NSS_SoftWareSlave_Set													(0X1U<<9 | 1<<8) //CR1 Bit9
#define SPI_NSS_SoftWareSlave_Reset													(0X1U<<9) //CR1 Bit9



//@ref BaudRate_Prescaler_define

//Bits 5:3 BR[2:0]: Baud rate control
//000: fPCLK/2
//001: fPCLK/4
//010: fPCLK/8
//011: fPCLK/16
//100: fPCLK/32
//101: fPCLK/64
//110: fPCLK/128
//111: fPCLK/256
#define SPI_BaudRate_Prescaler_2					(0X00000000U)
#define SPI_BaudRate_Prescaler_4					(0b001U<<3)
#define SPI_BaudRate_Prescaler_8					(0b010U<<3)
#define SPI_BaudRate_Prescaler_16					(0b011U<<3)
#define SPI_BaudRate_Prescaler_32					(0b100U<<3)
#define SPI_BaudRate_Prescaler_64					(0b101U<<3)
#define SPI_BaudRate_Prescaler_128					(0b110U<<3)
#define SPI_BaudRate_Prescaler_256					(0b111U<<3)



//@ref SPI_IRQ_Enable_define
//Bit 7 TXEIE: Tx buffer empty interrupt enable
//0: TXE interrupt masked
//1: TXE interrupt not masked. Used to generate an interrupt request when the TXE flag is set.
//Bit 6 RXNEIE: RX buffer not empty interrupt enable
//0: RXNE interrupt masked
//1: RXNE interrupt not masked. Used to generate an interrupt request when the RXNE flag is
//set.
//Bit 5 ERRIE: Error interrupt enable
//This bit controls the generation of an interrupt when an error condition occurs (CRCERR,
//OVR, MODF in SPI mode and UDR, OVR in I2S mode).
//0: Error interrupt is masked
//1: Error interrupt is enabled

#define SPI_IRQ_Enable_NONE				(uint32_t)(0)
#define SPI_IRQ_Enable_TXE			(uint32_t)(1<<7)
#define SPI_IRQ_Enable_RXNE			(uint32_t)(1<<6)
#define SPI_IRQ_Enable_ERRIE			(uint32_t)(1<<5)





/*
* ===============================================
* APIs Supported by "MCAL SPI DRIVER"
* ===============================================
*/

void MCAL_SPI_Init(SPI_TypeDef * SPIx, SPI_Config * SPI_cnfg);
void MCAL_SPI_DeInit(SPI_TypeDef * SPIx);
void MCAL_SPI_GPIO_Set_Pins(SPI_TypeDef * SPIx);
void MCAL_SPI_SendData(SPI_TypeDef * SPIx, uint16_t * pTxBuffer, enum Polling_mechanism  PollingEn);
void MCAL_SPI_ReceivData(SPI_TypeDef * SPIx, uint16_t * pRxBuffer, enum Polling_mechanism  PollingEn);
void MCAL_SPI_TX_RX(SPI_TypeDef * SPIx, uint16_t * pTxBuffer, enum Polling_mechanism  PollingEn);

#endif /* INC_STM32F103C6_SPI_DRIVER_H_ */
