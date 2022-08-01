/*
 * I2C_Slave_EEPROM.c
 *
 *  Created on: ٣٠‏/٠٧‏/٢٠٢٢
 *      Author: Omar
 */

#include "../inc/I2C_Slave_EEPROM.h"

void eeprom_init(void)
{
	//===========I2V_INIT======================
	//		PB6 : I2C1_SCL
	//		PB7 : I2C1_SDA

	I2C_Config I2C_CFG;

	//I2C Controller ACT AS A  MASTER

	I2C_CFG.General_Call_Address_Detection = I2C_General_Call_Address_Enable;
	I2C_CFG.I2C_ACK_Control = I2C_Ack_Enable;
	I2C_CFG.I2C_ClockSpeed = I2C_SCLK_SM_100K;
	I2C_CFG.I2C_Mode = I2C_mode_I2C;
	I2C_CFG.Stretch_Mode = I2C_Stretch_Mode_Enable;
	I2C_CFG.P_Slave_Event_CallBack = NULL;


	MCAL_I2C_GPIO_Set_Pins(I2C1);
	MCAL_I2C_Init(I2C1, &I2C_CFG);

}

unsigned char eeprom_write_Nbytes(unsigned int Memory_address, unsigned char *bytes, uint8_t Data_Length)
{
	uint8_t i=0;
	uint8_t buffer[256];
	buffer[0] = (uint8_t)(Memory_address>>8);   //upper Memory Address
	buffer[1] = (uint8_t)(Memory_address);		//Lower Memory Address

	for( i =2 ; i< (Data_Length+2) ; i++){

		buffer[i]= bytes[i-2];
	}

	MCAL_I2C_Master_TX(I2C1, EEPROM_Slave_Address, buffer, Data_Length+2, WithStop, Start);

	return 0;
}
unsigned char eeprom_read_byte(unsigned int address, unsigned char *dataOut, uint8_t dataLen)
{

	uint8_t i=0;
		uint8_t buffer[2];
		buffer[0] = (uint8_t)(address>>8);   //upper Memory Address
		buffer[1] = (uint8_t)(address);		//Lower Memory Address


		MCAL_I2C_Master_TX(I2C1, EEPROM_Slave_Address, buffer, 2, WithoutStop, Start);
		MCAL_I2C_Master_RX(I2C1, EEPROM_Slave_Address, dataOut, dataLen, WithStop, RepeatedSart);

		return 0;

}

