/*
 * lcd.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: Omar
 */

#ifndef LCD_H_
#define LCD_H_

#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>

#define LCD_PORT PORTA
#define DataDir_LCD_PORT DDRA
#define LCD_CTRL PORTB
#define DataDir_LCD_CTRL DDRB

#define RS_Switch 1
#define Rw_Switch 2
#define EN_Switch 3

#define EIGHT_BIT_MODE


#define LCD_Function_8BIT_1LINE (0x30)
#define LCD_Function_8BIT_2LINE (0x38)
#define LCD_Function_4BIT_1LINE (0x20)
#define LCD_Function_4BIT_2LINE (0x28)
#define LCD_Entry_Mode (0x06)
#define LCD_Display_OFF (0x08)
#define LCD_Display_ON_Cursor_ON (0x0E)
#define LCD_Display_ON_Cursor_OFF (0x0C)
#define LCD_Display_ON_Cursor _Blinking (0x0F)
#define LCD_Shift_entire_display_left (0x18)
#define LCD_Shift_entire_display_right (0x1C)
#define LCD_Move_cursor_left (0x10)
#define LCD_Move_cursor_right (0x14)
#define LCD_Clear_Display (0x01)

void LCD_INIT(void);
void LCD_WRITE_COMMAND(unsigned char command);
void LCD_WRITE_CHAR(unsigned char data);
void LCD_WRITE_STR(char* string);
void LCD_IS_BUSY(void);
#endif /* LCD_H_ */
