/*
 * lcd_driver.h
 *
 *  Created on: ٠٢‏/٠٧‏/٢٠٢٢
 *      Author: Omar
 */

#ifndef INC_LCD_DRIVER_H_
#define INC_LCD_DRIVER_H_


//-----------------------------
//Includes
#include "../../HAL/inc/lcd_driver.h"

#include "../../stm32_F103C6_drivers/inc/stm32f103c6.h"
#include "../stm32_F103C6_drivers/inc/stm32_F103C6_gpio_driver.h"

//-----------------------------

#define LCD_PORT GPIOA
#define LCD_CTRL GPIOA


#define RS_Switch 							   GPIO_PIN_8
#define Rw_Switch 							   GPIO_PIN_9
#define EN_Switch 							   GPIO_PIN_10

#define EIGHT_BIT_MODE


#define LCD_Function_8BIT_1LINE 				(0x30)
#define LCD_Function_8BIT_2LINE 				(0x38)
#define LCD_Function_4BIT_1LINE 				(0x20)
#define LCD_Function_4BIT_2LINE 				(0x28)
#define LCD_Entry_Mode 							(0x06)
#define LCD_Display_OFF							(0x08)
#define LCD_Display_ON_Cursor_ON 				(0x0E)
#define LCD_Display_ON_Cursor_OFF 				(0x0C)
#define LCD_Display_ON_Cursor _Blinking 		(0x0F)
#define LCD_Shift_entire_display_left 			(0x18)
#define LCD_Shift_entire_display_right 			(0x1C)
#define LCD_Move_cursor_left 					(0x10)
#define LCD_Move_cursor_right					(0x14)
#define LCD_Clear_Display 						(0x01)

void LCD_INIT(void);
void LCD_WRITE_COMMAND(unsigned char command);
void LCD_WRITE_CHAR(unsigned char data);
void LCD_WRITE_STR(char* string);
void LCD_IS_BUSY(void);
void LCD_clear_screen();


#endif /* INC_LCD_DRIVER_H_ */
