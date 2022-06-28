/*
 * lcd.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Omar
 */

#include "lcd.h"
int curr_pos=0;
void LCD_KICK(){
	LCD_CTRL &= ~(1<<EN_Switch);
	_delay_ms(30);
	LCD_CTRL |= (1<<EN_Switch);
}
void LCD_GOTO_XY(int l , int pos){
	if(l ==1){
		LCD_WRITE_COMMAND(0x80+pos);
	}
	if(l ==2){
		LCD_WRITE_COMMAND(0xc0+pos);
	}
}
void LCD_Clear_screen(){
	LCD_WRITE_COMMAND(LCD_Clear_Display);
}
void LCD_INIT(void){
	_delay_ms(20);
#ifdef EIGHT_BIT_MODE
	LCD_IS_BUSY();
	DataDir_LCD_CTRL |=(1<<EN_Switch)|(1<<Rw_Switch)|(1<<RS_Switch);
	LCD_CTRL &=~((1<<EN_Switch)|(1<<Rw_Switch)|(1<<RS_Switch));
	DataDir_LCD_PORT = 0xff;
	LCD_Clear_screen();
	LCD_WRITE_COMMAND(LCD_Function_8BIT_2LINE);
#endif

#ifdef FOUR_BIT_MODE
	LCD_WRITE_COMMAND(LCD_Function_4BIT_2LINE);
#endif
	LCD_WRITE_COMMAND(LCD_Entry_Mode);
	LCD_WRITE_COMMAND(LCD_Display_ON_Cursor_ON);

}

void LCD_WRITE_COMMAND(unsigned char command){
#ifdef EIGHT_BIT_MODE
	LCD_IS_BUSY();
	LCD_PORT = command;
	LCD_CTRL &=~((1<<Rw_Switch)|(1<<RS_Switch));
	LCD_KICK();
#endif

#ifdef FOUR_BIT_MODE
#endif
}
void LCD_WRITE_CHAR(unsigned char data){
#ifdef EIGHT_BIT_MODE
	LCD_IS_BUSY();
	LCD_PORT = data;
	LCD_CTRL &=~((1<<Rw_Switch)|(1<<RS_Switch));
	LCD_CTRL |=(1<<RS_Switch);
	LCD_KICK();
#endif

#ifdef FOUR_BIT_MODE
#endif
	if(++curr_pos >= 16);
	LCD_GOTO_XY(2,0);
}
void LCD_WRITE_STR(char* string){
	int count =0;
	while(*string){

		count++;
		if(count==16)
			LCD_GOTO_XY(2,0);
		else if(count ==32)
		{
			LCD_Clear_screen();
			LCD_GOTO_XY(1,0);
			count =0;
		}
		LCD_WRITE_CHAR(*string++);
	}
}
void LCD_IS_BUSY(void){

	DataDir_LCD_PORT = 0x00;
	LCD_CTRL |=(1<<Rw_Switch); //read mode
	LCD_CTRL &= ~(1<<RS_Switch);
	 LCD_KICK();
	 LCD_CTRL &= ~(1<<Rw_Switch);
}
