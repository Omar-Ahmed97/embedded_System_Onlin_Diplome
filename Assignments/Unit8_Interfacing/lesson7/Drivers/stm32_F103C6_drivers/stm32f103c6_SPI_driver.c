/*
 * stm32f103c6_SPI_driver.c
 *
 *  Created on: ٢١‏/٠٧‏/٢٠٢٢
 *      Author: Omar
 */



#include "../stm32_F103C6_drivers/inc/stm32f103c6_SPI_driver.h"


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

#define SPI1_INDEX				0
#define SPI2_INDEX				1


#define SPI_SR_TXE			((uint8_t)0x02)
#define SPI_SR_RXNE			((uint8_t)0x01)


/*
 * =========================================================================
 * 							Generic Functions
 * ==========================================================================
 */
	SPI_Config * Global_SPI_Config[2] = {NULL,NULL};
	SPI_Config  Global_SPI_Config1;
	SPI_Config  Global_SPI_Config2;
/*
 * =========================================================================
 * 							API'S Functions Definitions
 * ==========================================================================
 */

/**================================================================
* @Fn					- MCAL_SPI_Init
* @brief 				- initialize SPIx Registers  correspondin SPI_cnfg
* @param [in] 			- SPIx : where x can be (1,2,3,.. depending on device used)
* @param [in] 			- SPI_cnfg : SPI configuration Specified by the user
* @retval 				- none
//* Note					- Support for SPI Full Dublex Master /Slave only & NSS HW /SW for slave
 * 							-In case of master you have to configure pinnd drive it
*/
/**================================================================*/

void MCAL_SPI_Init(SPI_TypeDef * SPIx, SPI_Config * SPI_cnfg){
	//Saftey for register
	uint16_t tempReg_CR1 = 0;
	uint16_t tempReg_CR2 = 0;
	if(SPIx == SPI1)
	{
		Global_SPI_Config1 = *SPI_cnfg;
		Global_SPI_Config[SPI1_INDEX]= &Global_SPI_Config1;
		RCC_SPI1_CLK_EN();

	}else if(SPIx == SPI2)
	{
		Global_SPI_Config2 = *SPI_cnfg;
		Global_SPI_Config[SPI2_INDEX]= &Global_SPI_Config2;
		RCC_SPI2_CLK_EN();
	}


	//Bit 6 SPE: SPI enable
	tempReg_CR1 |= (0x1<<6);

	//Master Or Slave
	tempReg_CR1 |= SPI_cnfg->Device_Mode;

	//SPI Communication mode
	tempReg_CR1 |= SPI_cnfg->Communication_Mode;

	//SPI  Frame Format
	tempReg_CR1 |= SPI_cnfg->Frame_Format;

	//SPI  Data Size
	tempReg_CR1 |= SPI_cnfg->DataSize;

	//SPI	Clock Polarity
	tempReg_CR1 |= SPI_cnfg->CLKPolarity;

	//SPI  Clock Phase
	tempReg_CR1 |= SPI_cnfg->CLKPhase;

	//=======================NSS==================//
	if(SPI_cnfg->NSS == SPI_NSS_Hard_Master_NotMultiMaster  )
	{
		tempReg_CR2  |= SPI_cnfg->NSS;

	}else if(SPI_cnfg->NSS == SPI_NSS_Hard_Master_MultiMaster || SPI_cnfg->NSS == SPI_NSS_Hard_Slave)
	{
		tempReg_CR2  &= SPI_cnfg->NSS;
	}else
	{
		tempReg_CR1 |=  SPI_cnfg->NSS;
	}


	//SPI	Baud Rate
	tempReg_CR1 |= SPI_cnfg->BaudRate_Prescaler;

	// SPI interrupt enable

	if(SPI_cnfg->IRQ_Enable != SPI_IRQ_Enable_NONE)
	{
		//SPI_IRQ_Enable_define
		tempReg_CR2 |= SPI_cnfg->IRQ_Enable;

		if(SPIx == SPI1)
		{
			NVIC_IRQ35_SPI1_Enable;

		}else if(SPIx == SPI2)
		{
			NVIC_IRQ36_SPI2_Enable;
		}
	}

	SPIx->CR1 = tempReg_CR1;
	SPIx->CR2 = tempReg_CR2;
}

/**================================================================
* @Fn					- MCAL_SPI_DeInit
* @brief 				- Deinitialize SPIx Registers  correspondin SPI_cnfg
* @param [in] 			- SPIx : where x can be (1,2,3,.. depending on device used)
* @retval 				- none
//* Note					- none
*/
/**================================================================*/
void MCAL_SPI_DeInit(SPI_TypeDef * SPIx){

	if(SPIx == SPI1)
		{
			NVIC_IRQ35_SPI1_Disable ;
			RCC_SPI1_CLK_Reset();

		}else if(SPIx == SPI2)
		{
			NVIC_IRQ36_SPI2_Disable;
			RCC_SPI2_CLK_Reset();
		}


}
/**================================================================
* @Fn					- MCAL_SPI_GPIO_Set_Pins
* @brief 				- Set GPIO PINs that is connected to  SPI Peripheral
* @param [in] 			- SPIx : where x can be (1,2,3,.. depending on device used)
* @retval 				- none
* Note					-  none.
*/
/**================================================================*/
void MCAL_SPI_GPIO_Set_Pins(SPI_TypeDef * SPIx)
{
	GPIO_PinConfig_t pin_cnfg;

	if(SPIx == SPI1){
		//PA4 : SPI_NSS
		//PA5 : SPI_SCK
		//PA6 : SPI_MISO
		//PA7 : SPI_MOSI

		if(Global_SPI_Config[SPI1_INDEX]->Device_Mode == SPI_Device_Mode_MASTER)
		{
			//PA4 : SPI_NSS

		switch(Global_SPI_Config[SPI1_INDEX]->NSS)
		{
		case SPI_NSS_Hard_Master_MultiMaster:
			//Hardware master /slave Input floating
			pin_cnfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
			pin_cnfg.GPIO_PinNumber= GPIO_PIN_4;
			MCAL_GPIO_Init(GPIOA, &pin_cnfg);
			break;

		case SPI_NSS_Hard_Master_NotMultiMaster:
			//Hardware master/ NSS output enabled Alternate function push-pull
			pin_cnfg.GPIO_PinNumber= GPIO_PIN_4;
			pin_cnfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			pin_cnfg.GPIO_Output_Speed = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOA, &pin_cnfg);

			break;
		}
		//PA5 : SPI_SCK
//Master Alternate function push-pull
		pin_cnfg.GPIO_PinNumber= GPIO_PIN_5;
		pin_cnfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
		pin_cnfg.GPIO_Output_Speed = GPIO_SPEED_10M;
		MCAL_GPIO_Init(GPIOA, &pin_cnfg);

		//PA6 : SPI_MISO
		//Full duplex / master Input floating / Input pull-up
		pin_cnfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
		pin_cnfg.GPIO_PinNumber= GPIO_PIN_6;
		MCAL_GPIO_Init(GPIOA, &pin_cnfg);

		//PA7 : SPI_MOSI
//Full duplex / master Alternate function push-pull
		pin_cnfg.GPIO_PinNumber= GPIO_PIN_7;
		pin_cnfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
		pin_cnfg.GPIO_Output_Speed = GPIO_SPEED_10M;
		MCAL_GPIO_Init(GPIOA, &pin_cnfg);

		}else	//slave
		{
			//PA4 : SPI_NSS

			if(Global_SPI_Config[SPI1_INDEX]->NSS == SPI_NSS_Hard_Slave)
			{
				//Hardware master /slave Input floating/ Input pull-up / Input pull-down
				//Hardware master /slave Input floating
				pin_cnfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
				pin_cnfg.GPIO_PinNumber= GPIO_PIN_4;
				MCAL_GPIO_Init(GPIOA, &pin_cnfg);
			}

			//PA5 : SPI_SCK
			//Slave Input floating
			pin_cnfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
			pin_cnfg.GPIO_PinNumber= GPIO_PIN_5;
			MCAL_GPIO_Init(GPIOA, &pin_cnfg);

			//PA6 : SPI_MISO
			//Full duplex / slave (point to point) Alternate function push-pull
			//to do Full duplex / slave (multi-slave) Alternate function open drain
			pin_cnfg.GPIO_PinNumber= GPIO_PIN_6;
			pin_cnfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			pin_cnfg.GPIO_Output_Speed = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOA, &pin_cnfg);

			//PA7 : SPI_MOSI
			//Full duplex / slave Input floating / Input pull-up
			pin_cnfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
			pin_cnfg.GPIO_PinNumber= GPIO_PIN_7;
			MCAL_GPIO_Init(GPIOA, &pin_cnfg);
		}

	}else if(SPIx == SPI2)
	{
		//PB12 : SPI_NSS
		//PB13 : SPI_SCK
		//PB14 : SPI_MISO
		//PB15 : SPI_MOSI

		if(Global_SPI_Config[SPI2_INDEX]->Device_Mode == SPI_Device_Mode_MASTER)
				{
			//PB12 : SPI_NSS

				switch(Global_SPI_Config[SPI2_INDEX]->NSS)
				{
				case SPI_NSS_Hard_Master_MultiMaster:
					//Hardware master /slave Input floating
					pin_cnfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
					pin_cnfg.GPIO_PinNumber= GPIO_PIN_12;
					MCAL_GPIO_Init(GPIOB, &pin_cnfg);
					break;

				case SPI_NSS_Hard_Master_NotMultiMaster:
					//Hardware master/ NSS output enabled Alternate function push-pull
					pin_cnfg.GPIO_PinNumber= GPIO_PIN_12;
					pin_cnfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
					pin_cnfg.GPIO_Output_Speed = GPIO_SPEED_10M;
					MCAL_GPIO_Init(GPIOB, &pin_cnfg);

					break;
				}
				//PB13 : SPI_SCK
		//Master Alternate function push-pull
				pin_cnfg.GPIO_PinNumber= GPIO_PIN_13;
				pin_cnfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
				pin_cnfg.GPIO_Output_Speed = GPIO_SPEED_10M;
				MCAL_GPIO_Init(GPIOB, &pin_cnfg);

				//PB14 : SPI_MISO
				//Full duplex / master Input floating / Input pull-up
				pin_cnfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
				pin_cnfg.GPIO_PinNumber= GPIO_PIN_14;
				MCAL_GPIO_Init(GPIOB, &pin_cnfg);

				//PB15 : SPI_MOSI
		//Full duplex / master Alternate function push-pull
				pin_cnfg.GPIO_PinNumber= GPIO_PIN_15;
				pin_cnfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
				pin_cnfg.GPIO_Output_Speed = GPIO_SPEED_10M;
				MCAL_GPIO_Init(GPIOB, &pin_cnfg);

				}}else	//slave
				{
					//PB12 : SPI_NSS

					if(Global_SPI_Config[SPI2_INDEX]->NSS == SPI_NSS_Hard_Slave)
					{
						//Hardware master /slave Input floating/ Input pull-up / Input pull-down
						//Hardware master /slave Input floating
						pin_cnfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
						pin_cnfg.GPIO_PinNumber= GPIO_PIN_12;
						MCAL_GPIO_Init(GPIOB, &pin_cnfg);
					}

					//PB13 : SPI_SCK
					//Slave Input floating
					pin_cnfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
					pin_cnfg.GPIO_PinNumber= GPIO_PIN_13;
					MCAL_GPIO_Init(GPIOB, &pin_cnfg);

					//PB14 : SPI_MISO
					//Full duplex / slave (point to point) Alternate function push-pull
					//to do Full duplex / slave (multi-slave) Alternate function open drain
					pin_cnfg.GPIO_PinNumber= GPIO_PIN_14;
					pin_cnfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
					pin_cnfg.GPIO_Output_Speed = GPIO_SPEED_10M;
					MCAL_GPIO_Init(GPIOB, &pin_cnfg);

					//PB15 : SPI_MOSI
					//Full duplex / slave Input floating / Input pull-up
					pin_cnfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
					pin_cnfg.GPIO_PinNumber= GPIO_PIN_15;
					MCAL_GPIO_Init(GPIOB, &pin_cnfg);
	}

}


/**================================================================
* @Fn					- MCAL_SPI_SendData
* @brief 				- Send Data using SPI Registers  correspondin SPI_cnfg
* @param [in] 			- SPIx : where x can be (1,2,3,.. depending on device used)
* @param [in] 			- pTxBuffer
* @param [in] 			- PollingEn : Enable polling or disabling it
* @retval 				- none
* Note					-  none.
*/
/**================================================================*/

void MCAL_SPI_SendData(SPI_TypeDef * SPIx, uint16_t * pTxBuffer, enum Polling_mechanism  PollingEn)
{
	if(PollingEn == enable)
		while(!(SPIx->SR & SPI_SR_TXE));
	SPIx->DR = *pTxBuffer;

}
/**================================================================
* @Fn					- MCAL_SPI_ReceivData
* @brief 				- Recieve Data Using SPI Registers  correspondin SPI_cnfg
* @param [in] 			- SPIx : where x can be (1,2,3,.. depending on device used)
* @param [in] 			- pRxBuffer
* @param [in] 			- PollingEn : Enable polling or disabling it
* @retval 				- none
* Note					-  none.
*/
/**================================================================*/
void MCAL_SPI_ReceivData(SPI_TypeDef * SPIx, uint16_t * pRxBuffer, enum Polling_mechanism  PollingEn)
{
	if(PollingEn == enable)
		while(!(SPIx->SR & SPI_SR_RXNE));
	*pRxBuffer = SPIx->DR ;
}
/**================================================================
* @Fn					- MCAL_SPI_TX_RX
* @brief 				- Transmit and  Recieve Data Using SPI Registers  correspondin SPI_cnfg
* @param [in] 			- SPIx : where x can be (1,2,3,.. depending on device used)
* @param [in] 			- pTxBuffer
* @param [in] 			- PollingEn : Enable polling or disabling it
* @retval 				- none
* Note					-  none.
*/
/**================================================================*/

void MCAL_SPI_TX_RX(SPI_TypeDef * SPIx, uint16_t * pTxBuffer, enum Polling_mechanism  PollingEn)
{
	if(PollingEn == enable)
		while(!(SPIx->SR & SPI_SR_TXE));
	SPIx->DR = *pTxBuffer;

	if(PollingEn == enable)
		while(!(SPIx->SR & SPI_SR_RXNE));
	*pTxBuffer = SPIx->DR ;
}


/*
 * =========================================================================
 * 							ISR
 * ==========================================================================
 */

void SPI1_IRQHandler(void){
	struct S_IRQ_SRC irq_src;

	irq_src.TXE = ((SPI1->SR &(1<<1))>>1);
	irq_src.RXNE = ((SPI1->SR &(1<<0))>>0);
	irq_src.ERRI = ((SPI1->SR &(1<<4))>>4);

	Global_SPI_Config[SPI1_INDEX]->P_IRQ_CallBack(irq_src);

}

void SPI2_IRQHandler(void){

	struct S_IRQ_SRC irq_src;

	irq_src.TXE = ((SPI2->SR &(1<<1))>>1);
	irq_src.RXNE = ((SPI2->SR &(1<<0))>>0);
	irq_src.ERRI = ((SPI2->SR &(1<<4))>>4);

	Global_SPI_Config[SPI2_INDEX]->P_IRQ_CallBack(irq_src);
}
