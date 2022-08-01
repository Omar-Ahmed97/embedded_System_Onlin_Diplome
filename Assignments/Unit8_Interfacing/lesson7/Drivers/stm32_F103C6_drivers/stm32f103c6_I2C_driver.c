/*
 * stm32f103c6_I2C_driver.c
 *
 *  Created on: ٢٨‏/٠٧‏/٢٠٢٢
 *      Author: Omar
 */


#include "../stm32_F103C6_drivers/inc/stm32f103c6_I2C_driver.h"


/*
 * =========================================================================
 * 							Generic Variables
 * ==========================================================================
 */

I2C_Config Global_I2C_Config[2] = {NULL,NULL};

/*
 * =========================================================================
 * 							Generic Macros
 * ==========================================================================
 */

#define I2C1_Index				0
#define I2C2_Index				1




/*
 * =========================================================================
 * 							Generic Functions
 * ==========================================================================
 */

/*
 * =========================================================================
 * 							API'S Functions Definitions
 * ==========================================================================
 */

/**================================================================
* @Fn					- MCAL_I2C_Init
* @brief 				- initialize I2Cx Registers  correspondin I2C_cnfg
* @param [in] 			- I2Cx : where x can be (1,2,3,.. depending on device used)
* @param [in] 			- I2C_Init_Struct : I2C configuration Specified by the user
* @retval 				- none
//* Note
 *
*/
/**================================================================*/
void MCAL_I2C_Init(I2C_TypeDef* I2Cx, I2C_Config* I2C_Init_Struct)
{
	uint16_t tmpreg, freqReg;
	uint32_t pclk1 = 8000000;
	uint16_t result = 0;
	//Enable RCC
	if(I2Cx == I2C1){

		Global_I2C_Config[I2C1_Index] = *I2C_Init_Struct;
		RCC_I2C1_CLK_EN();

	}else
	{
		Global_I2C_Config[I2C2_Index] = *I2C_Init_Struct;
		RCC_I2C2_CLK_EN();

	}
	if(I2C_Init_Struct->I2C_Mode == I2C_mode_I2C)
	{
		/*-------------------------------------*/
		//Bits 5:0 FREQ[5:0]: Peripheral clock frequency
		tmpreg = I2Cx->CR2;
		tmpreg &= ~(I2C_CR2_FREQ);
		pclk1 = MCAL_RCC_GetPCLK1Freq();
		freqReg = (uint16_t)(pclk1 / 1000000);
		tmpreg |= freqReg;

		I2Cx->CR2 = tmpreg ;

		//Configure the rise time register
		/* disable the selected I2C */
		I2Cx->CR1 &=~(I2C_CR1_PE);

		tmpreg =0;

		/* Configure Speed in Standard mode		 */

		if(I2C_Init_Struct->I2C_ClockSpeed == I2C_SCLK_SM_50K || I2C_Init_Struct->I2C_ClockSpeed == I2C_SCLK_SM_100K)
		{
			// Tclk/2 = CRR * Tpclk1
			//CRR = Fpclk1 / (2 * I2C_Clock_fre )

			result = (uint16_t)(pclk1 /( I2C_Init_Struct->I2C_ClockSpeed<<1  ) );
			tmpreg |= result;

			/*Write to CRR*/
			I2Cx->CCR = tmpreg;

			tmpreg = 0;
			/*--------------------------Configure the rise time register--------------*/
				//	Bits 5:0 TRISE[5:0]: Maximum rise time in Fm/Sm mode (Master mode)
			result = (uint16_t)(freqReg )+1;
			tmpreg |= result;
			/*Write to I2Cx->TRISE*/
			I2Cx->TRISE = tmpreg;

		}else
		{
			//Fast Mode Not Supported
		}

	/* Program the I2C_CR1 register to enable the peripheral*/
		tmpreg = 0;
		tmpreg = I2Cx->CR1;

		tmpreg |=(uint16_t) (I2C_Init_Struct->I2C_ACK_Control) | (I2C_Init_Struct->General_Call_Address_Detection) | (I2C_Init_Struct->I2C_Mode) |(I2C_Init_Struct->Stretch_Mode);

		/*Write to I2Cx->CR1*/
		I2Cx->CR1 = tmpreg;

		/* Program the I2C_OAR1 OAR2 registerl*/
		tmpreg=0;
		if(I2C_Init_Struct->S_I2C_Slave_Address.Enable_Dual_Address == 1)
		{
			tmpreg = I2C_OAR2_ENDUAL;
			tmpreg |= I2C_Init_Struct->S_I2C_Slave_Address.Secondary_Slave_Address << I2C_OAR2_ADD2_Pos ;
			I2Cx->OAR2 = tmpreg;
		}
		tmpreg=0;
		tmpreg |= I2C_Init_Struct->S_I2C_Slave_Address.Primary_Slave_Address << 1;
		tmpreg |= I2C_Init_Struct->S_I2C_Slave_Address.I2C_Addressing_Slave_mode;
		I2Cx->OAR1 = tmpreg;

	}

	//interrupt  Mode (Slave Mode ) //Check callback != NULL
	if(I2C_Init_Struct->P_Slave_Event_CallBack != NULL)	//then Enable IRQ State Mode
	{
		I2Cx->CR2 |= (I2C_CR2_ITBUFEN) |(I2C_CR2_ITERREN) |(I2C_CR2_ITEVTEN);

		if(I2Cx == I2C1)
		{
			NVIC_IRQ31_I2C1_EV_Enable;
			NVIC_IRQ32_I2C1_ER_Enable;
		}else
		{
			NVIC_IRQ33_I2C2_EV_Enable;
			NVIC_IRQ34_I2C2_ER_Enable;
		}

		I2Cx->SR1 = 0;
		I2Cx->SR2 = 0;

	}


	/*  SMBUS Not Supported*/
	I2Cx->CR1 |= I2C_CR1_PE;

}
/**================================================================
* @Fn					- MCAL_I2C_DInit
* @brief 				- Deinitialize I2Cx Registers  to reset Value
* @param [in] 			- none
* @retval 				- none
//* Note
 *
*/
/**================================================================*/
void MCAL_I2C_DInit(I2C_TypeDef* I2Cx)
{

	if(I2Cx == I2C1)
	{
		NVIC_IRQ31_I2C1_EV_Disable;
		NVIC_IRQ32_I2C1_ER_Disable;
		RCC_I2C1_CLK_Reset();
	}else
	{
		NVIC_IRQ33_I2C2_EV_Disable;
		NVIC_IRQ34_I2C2_ER_Disable;
		RCC_I2C2_CLK_Reset();

	}


}
/**================================================================
* @Fn					- I2C_GPIO_Set_Pins
* @brief 				- set Gpio pins connectected to I2C peripheral according to recommended configuration
* @param [in] 			-I2Cx : where x can be (1,2,3,.. depending on device used)
* @retval 				- none
//* Note
 *
*/
/**================================================================*/
void MCAL_I2C_GPIO_Set_Pins(I2C_TypeDef* I2Cx)
{
	GPIO_PinConfig_t pinCnfg;
	if(I2Cx == I2C1)
		{
		// PB6 :SCL
		//PB7 :SDA
		pinCnfg.GPIO_PinNumber =GPIO_PIN_6;
		pinCnfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_OD;
		pinCnfg.GPIO_Output_Speed = GPIO_SPEED_10M;
		MCAL_GPIO_Init(GPIOB, &pinCnfg);

		pinCnfg.GPIO_PinNumber =GPIO_PIN_7;
		pinCnfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_OD;
		pinCnfg.GPIO_Output_Speed = GPIO_SPEED_10M;
		MCAL_GPIO_Init(GPIOB, &pinCnfg);

		}else
		{
			// PB10 :SCL
			//PB11 :SDA
			pinCnfg.GPIO_PinNumber =GPIO_PIN_10;
			pinCnfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_OD;
			pinCnfg.GPIO_Output_Speed = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOB, &pinCnfg);

			pinCnfg.GPIO_PinNumber =GPIO_PIN_11;
			pinCnfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_OD;
			pinCnfg.GPIO_Output_Speed = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOB, &pinCnfg);


		}


}



/**================================================================
* @Fn					- MCAL_I2C_Master_TX
* @brief 				- Set I2C to tansmit data buffer from dataOut  with length datalen
* @param [in] 			-I2Cx : where x can be (1,2,3,.. depending on device used)
* @param [in] 			-devAdd: the address of the chosen slave
* @param [in] 			-dataOut: buffer of first element
* @param [in] 			-dataLen : number of elements
* @retval 				- none
//* Note
 *
*/
/**================================================================*/
void MCAL_I2C_Master_TX(I2C_TypeDef *I2Cx , uint16_t devAdd,uint8_t* dataOut, uint32_t dataLen , Stop_Condition Stop , Repeated_Start start)
{
	int i =0;

	//to do support time out to configure timer for specific duration rase interrup
	// so any check flag has expiration time

	//1. Generate Star Condition
	I2C_GenerateStar(I2Cx , ENABLE,  start);

	//2.Wait for EV5
	//EV5: SB=1, cleared by reading SR1 register followed by writing DR register with Address.
	while( !(I2C_GetFlagStatus( I2Cx, EV5)));

	//3- Send Address
	I2C_SendAddress( I2Cx,  devAdd , I2C_Direction_Transmitter);

	//2.Wait for EV6
	//EV6: ADDR=1, cleared by reading SR1 register followed by reading SR2.
	while( !(I2C_GetFlagStatus( I2Cx, EV6)));

	//4. Busy MSL TXE TRA
	while( !(I2C_GetFlagStatus( I2Cx, MASTER_BYTE_TRANSMITING)));

	for( i= 0; i< dataLen ; i++)
	{
		I2Cx->DR = dataOut[i];
		//5.Wait EV8
		//EV8: TxE=1, shift register not empty, d . ata register empty, cleared by writing DR register

		while( !(I2C_GetFlagStatus( I2Cx, EV8)));
	}
	//wait for EV8_2
	//EV8_2: TxE=1, BTF = 1, Program Stop request. TxE and BTF are cleared by hardware by the Stop condition
	while( !(I2C_GetFlagStatus( I2Cx, EV8_2)));

	if(Stop == WithStop){
		//Send Stop Condition
		 I2C_GenerateStop(I2Cx , ENABLE);
	}



}
void MCAL_I2C_Master_RX(I2C_TypeDef *I2Cx , uint16_t devAdd,uint8_t* dataOut, uint32_t dataLen , Stop_Condition Stop , Repeated_Start start)
{
	uint8_t index = I2Cx == I2C1 ? I2C1_Index : I2C2_Index;
	int i =0;
	//to do support time out to configure timer for specific duration rase interrup
		// so any check flag has expiration time

		//1. Generate Star Condition
		I2C_GenerateStar(I2Cx , ENABLE,  start);

		//2.Wait for EV5
		//EV5: SB=1, cleared by reading SR1 register followed by writing DR register with Address.
		while( !(I2C_GetFlagStatus( I2Cx, EV5)));

		//3- Send Address
		I2C_SendAddress( I2Cx,  devAdd , I2C_Direction_Recieve);

		//2.Wait for EV6
		//EV6: ADDR=1, cleared by reading SR1 register followed by reading SR2.
		while( !(I2C_GetFlagStatus( I2Cx, EV6)));

		I2C_AcknowledgeConfig(I2Cx,ENABLE);

		if(dataLen)
		{
			for( i= dataLen; i >= 1 ; i--)
			{

				//5.Wait EV7
				//%62X.%CLEAREDBYREADING$2REGISTER
				while( !(I2C_GetFlagStatus( I2Cx, EV7)));

				*dataOut = I2Cx->DR ;
				dataOut++;
			}
			I2C_AcknowledgeConfig(I2Cx,DISABLE);


		}
		if(Stop == WithStop)
		{
			//7-Send Stop Condition
			I2C_GenerateStop(I2Cx, ENABLE);
		}
		if(Global_I2C_Config[index].I2C_ACK_Control == I2C_Ack_Enable)
		{
			I2C_AcknowledgeConfig(I2Cx,ENABLE);
		}



}

void I2C_GenerateStar(I2C_TypeDef *I2Cx , FunctionalState NewState, Repeated_Start Start)
{
	if(Start != RepeatedSart)
	{
		//check if the bud is idle
		while(  I2C_GetFlagStatus( I2Cx, I2C_FLAG_BUSY) );



	}

	//		Bit 8 START: Start generation
	//		This bit is set and cleared by software and cleared by hardware when start is sent or PE=0.
	//		In Master Mode:
	//		0: No Start generation
	//		1: Repeated start generation
	//		In Slave mode:
	//		0: No Start generation
	//		1: Start generation when the bus is free

			if(NewState != DISABLE)
			{
				/*Generate Starte Condition*/
				I2Cx->CR1 |= I2C_CR1_START;
			}
			else
			{
				/*Disable  Starte Condition Generation*/
				I2Cx->CR1 &= ~(I2C_CR1_START);
			}

}


FlagStatus I2C_GetFlagStatus(I2C_TypeDef* I2Cx, Status Flag)
{
	FlagStatus bitstatus = RESET;
	volatile uint32_t dummy_Read;
	uint32_t flag1 = 0 ,flag2 =0 , lastevent =0;


	switch(Flag)
	{
	case I2C_FLAG_BUSY:
	{
//		Bit 1 BUSY: Bus busy
//		0: No communication on the bus
//		1: Communication ongoing on the bus
//		– Set by hardware on detection of SDA or SCL low
//		– cleared by hardware on detection of a Stop condition.
//		It indicates a communication in progress on the bus. This information is still updated when
//		the interface is disabled (PE=0).

		if( (I2Cx->SR2) & (I2C_SR2_BUSY) )
			bitstatus = SET;
		else
			bitstatus = RESET;
		break;
	}
	case EV5:
	{

//		Bit 0 SB: Start bit (Master mode)
//		0: No Start condition
//		1: Start condition generated.
//		– Set when a Start condition generated.
//		– Cleared by software by reading the SR1 register followed by writing the DR register, or by
//		hardware when PE=0		the interface is disabled (PE=0).

		if( (I2Cx->SR1) & (I2C_SR1_SB) )
			bitstatus = SET;
		else
			bitstatus = RESET;
		break;
	}
	//EV6: ADDR=1, cleared by reading SR1 register followed by reading SR2
	case EV6:
		{
//
//			Bit 1 ADDR: Address sent (master mode)/matched (slave mode)
//			This bit is cleared by software reading SR1 register followed reading SR2, or by hardware
//			when PE=0.
//			Address matched (Slave)
//			0: Address mismatched or not received.
//			1: Received address matched.
//			– Set by hardware as soon as the received slave address matched with the OAR registers
//			content or a general call or a SMBus Device Default Address or SMBus Host or SMBus Alert
//			is recognized. (when enabled depending on configuration).
//			Note: In slave mode, it is recommended to perform the complete clearing sequence (READ
//			SR1 then READ SR2) after ADDR is set. Refer to Figure 272.
//			Address sent (Master)
//			0: No end of address transmission
//			1: End of address transmission
//			– For 10-bit addressing, the bit is set after the ACK of the 2nd byte.
//			– For 7-bit addressing, the bit is set after the ACK of the byte.
//			Note: ADDR is not set after a NACK reception
			if( (I2Cx->SR1) & (I2C_SR1_ADDR) )
				bitstatus = SET;
			else
				bitstatus = RESET;

			if(I2Cx->SR2);
			break;
		}
	case EV8_1:
	case EV8:
			{
//				Bit 7 TxE: Data register empty (transmitters)
//				0: Data register not empty
//				1: Data register empty
//				– Set when DR is empty in transmission. TxE is not set during address phase.
//				– Cleared by software writing to the DR register or by hardware after a start or a stop condition
//				or when PE=0.
//				TxE is not set if either a NACK is received, or if next byte to be transmitted is PEC (PEC=1)
//				Note: TxE is not cleared by writing the first data being transmitted, or by writing data when
//				BTF is set, as in both cases the data register is still empty
				if( (I2Cx->SR1) & (I2C_SR1_TXE) )
					bitstatus = SET;
				else
					bitstatus = RESET;


				break;
			}

	case EV8_2:
				{
//					Bit 2 BTF: Byte transfer finished
//					0: Data byte transfer not done
//					1: Data byte transfer succeeded
//					– Set by hardware when NOSTRETCH=0 and:
//					– In reception when a new byte is received (including ACK pulse) and DR has not been read
//					yet (RxNE=1).
//					– In transmission when a new byte should be sent and DR has not been written yet (TxE=1).
//					– Cleared by software reading SR1 followed by either a read or write in the DR register or by
//					hardware after a start or a stop condition in transmission or when PE=0.
//					Note: The BTF bit is not set after a NACK reception
//					The BTF bit is not set if next byte to be transmitted is the PEC (TRA=1 in I2C_SR2
//					register and PEC=1 in I2C_CR1 register)
					if( (I2Cx->SR1) & (I2C_SR1_BTF) )
						bitstatus = SET;
					else
						bitstatus = RESET;


					break;
				}
	case EV7:
				{
//					Bit 6 RxNE: Data register not empty (receivers)
//					0: Data register empty
//					1: Data register not empty
//					– Set when data register is not empty in receiver mode. RxNE is not set during address phase.
//					– Cleared by software reading or writing the DR register or by hardware when PE=0.
//					RxNE is not set in case of ARLO event.
//					Note: RxNE is not cleared by reading data when BTF is set, as the data register is still full

					if( (I2Cx->SR1) & (I2C_SR1_RXNE) )
						bitstatus = SET;
					else
						bitstatus = RESET;


					break;
				}
	case MASTER_BYTE_TRANSMITING:
			{

				/*Read The I2Cx Statu Register*/
				flag1 = I2Cx->SR1;
				flag2 = I2Cx->SR2;
				flag2 = flag2<<16;
				/*Get the last Event value from I2C Statu Register*/
				lastevent = (flag1 | flag2) & ((uint32_t) 0xffffffff);
				//Check whether lastevent contain THE I2C_EVENT
				if((lastevent & MASTER_BYTE_TRANSMITING) == MASTER_BYTE_TRANSMITING)
					bitstatus = SET;
				else
					bitstatus = RESET;
			}
	}
return bitstatus;
}

void I2C_SendAddress(I2C_TypeDef* I2Cx, uint16_t Address , I2C_Direction Direction)
{
	uint8_t index = I2Cx == I2C1 ? I2C1_Index : I2C2_Index;

	if(Global_I2C_Config[index].I2C_Mode == I2C_Addressing_Slave_mode_7Bit)
	{
		// Send Address
		I2Cx->DR = (Address << 1 | Direction);

	}
	else
	{
		//Not Supported
	}




}

void I2C_GenerateStop(I2C_TypeDef *I2Cx , FunctionalState NewState)
{
	if(NewState != DISABLE)
		{
			/*Generate Stop Condition*/
			I2Cx->CR1 |= I2C_CR1_STOP;
		}
		else
		{
			/*Disable  Stop Condition Generation*/
			I2Cx->CR1 &= ~(I2C_CR1_STOP);
		}

}

void I2C_AcknowledgeConfig(I2C_TypeDef *I2Cx,FunctionalState NewState)
{
	if(NewState != DISABLE)
		{
			/*Generate Stop Condition*/
			I2Cx->CR1 |= I2C_CR1_ACK;
		}
		else
		{
			/*Disable  Stop Condition Generation*/
			I2Cx->CR1 &= ~(I2C_CR1_ACK);
		}
}


void MCAL_I2C_Slave_SendData(I2C_TypeDef *I2Cx ,uint8_t data)
{
	I2Cx->DR = data;
}
uint8_t MCAL_I2C_Slave_RX(I2C_TypeDef *I2Cx )
{
	return (uint8_t)I2Cx->DR;

}


void I2C1_EV_IRQHandler()
{

}

void I2C1_ER_IRQHandler()
{

}
void I2C2_EV_IRQHandler()
{

}
void I2C2_ER_IRQHandler()
{

}
