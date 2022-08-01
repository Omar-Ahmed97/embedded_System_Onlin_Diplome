/*
 * I2C_Slave_EEPROM.h
 *
 *  Created on: ٣٠‏/٠٧‏/٢٠٢٢
 *      Author: Omar
 */

#ifndef INC_I2C_SLAVE_EEPROM_H_
#define INC_I2C_SLAVE_EEPROM_H_


#include "../stm32_F103C6_drivers/inc/stm32f103c6_I2C_driver.h"


#define EEPROM_Slave_Address	0x2A

void eeprom_init(void);
unsigned char eeprom_write_Nbytes(unsigned int Memory_address, unsigned char *bytes, uint8_t Data_Length);
unsigned char eeprom_read_byte(unsigned int address, unsigned char *dataOut, uint8_t dataLen);


#endif /* INC_I2C_SLAVE_EEPROM_H_ */
