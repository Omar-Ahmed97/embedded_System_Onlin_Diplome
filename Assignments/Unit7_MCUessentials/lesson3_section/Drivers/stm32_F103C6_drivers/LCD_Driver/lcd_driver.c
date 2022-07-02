/*
 * lcd_driver.c
 *
 *  Created on: ٠٢‏/٠٧‏/٢٠٢٢
 *      Author: Omar
 */

#include "../../stm32_F103C6_drivers/inc/lcd_driver.h"

//int curr_pos=0;

GPIO_PinConfig_t PinCfg;



void LCD_DataDir_Input(){

	// GPIO_PIN_0 input HighZ Floating input (reset state)
	PinCfg.GPIO_PinNumber = GPIO_PIN_0;
	PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_Init(LCD_PORT, &PinCfg);


	// GPIO_PIN_1 input HighZ Floating input (reset state)
	PinCfg.GPIO_PinNumber = GPIO_PIN_1;
	PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_Init(LCD_PORT, &PinCfg);

	// GPIO_PIN_2 input HighZ Floating input (reset state)
	PinCfg.GPIO_PinNumber = GPIO_PIN_2;
	PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_Init(LCD_PORT, &PinCfg);

	// GPIO_PIN_3 input HighZ Floating input (reset state)
	PinCfg.GPIO_PinNumber = GPIO_PIN_3;
	PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_Init(LCD_PORT, &PinCfg);


	// GPIO_PIN_4 input HighZ Floating input (reset state)
	PinCfg.GPIO_PinNumber = GPIO_PIN_4;
	PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_Init(LCD_PORT, &PinCfg);

	// GPIO_PIN_5 input HighZ Floating input (reset state)
	PinCfg.GPIO_PinNumber = GPIO_PIN_5;
	PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_Init(LCD_PORT, &PinCfg);

	// GPIO_PIN_6 input HighZ Floating input (reset state)
	PinCfg.GPIO_PinNumber = GPIO_PIN_6;
	PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_Init(LCD_PORT, &PinCfg);

	// GPIO_PIN_7 input HighZ Floating input (reset state)
	PinCfg.GPIO_PinNumber = GPIO_PIN_7;
	PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_Init(LCD_PORT, &PinCfg);


}

void LCD_DataDir_Output(){
	///GPIO_PIN_0 (output PUSH pull Mode)
	//01: Output mode, max speed 10 MHz.
	PinCfg.GPIO_PinNumber = GPIO_PIN_0;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(GPIOA, &PinCfg);

	///GPIO_PIN_1 (output PUSH pull Mode)
	//01: Output mode, max speed 10 MHz.
	PinCfg.GPIO_PinNumber = GPIO_PIN_1;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(GPIOA, &PinCfg);

	///GPIO_PIN_2 (output PUSH pull Mode)
	//01: Output mode, max speed 10 MHz.
	PinCfg.GPIO_PinNumber = GPIO_PIN_2;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(GPIOA, &PinCfg);

	///GPIO_PIN_3 (output PUSH pull Mode)
	//01: Output mode, max speed 10 MHz.
	PinCfg.GPIO_PinNumber = GPIO_PIN_3;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(GPIOA, &PinCfg);

	///GPIO_PIN_4 (output PUSH pull Mode)
	//01: Output mode, max speed 10 MHz.
	PinCfg.GPIO_PinNumber = GPIO_PIN_4;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(GPIOA, &PinCfg);

	///GPIO_PIN_5 (output PUSH pull Mode)
	//01: Output mode, max speed 10 MHz.
	PinCfg.GPIO_PinNumber = GPIO_PIN_5;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(GPIOA, &PinCfg);

	///GPIO_PIN_6 (output PUSH pull Mode)
	//01: Output mode, max speed 10 MHz.
	PinCfg.GPIO_PinNumber = GPIO_PIN_6;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(GPIOA, &PinCfg);

	///GPIO_PIN_7 (output PUSH pull Mode)
	//01: Output mode, max speed 10 MHz.
	PinCfg.GPIO_PinNumber = GPIO_PIN_7;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(GPIOA, &PinCfg);
}

void LCD_clear_screen() {
	LCD_WRITE_COMMAND(LCD_Clear_Display);
}

void LCD_KICK(){

	//	LCD_CTRL |= (1<<EN_Switch);
		MCAL_GPIO_WritePin(LCD_CTRL, EN_Switch, GPIO_PIN_SET);

		wait_ms(30);

//	LCD_CTRL &= ~(1<<EN_Switch);
	MCAL_GPIO_WritePin(LCD_CTRL, EN_Switch, GPIO_PIN_RESET);


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



	wait_ms(20);

		PinCfg.GPIO_PinNumber = RS_Switch;
		PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
		PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
		MCAL_GPIO_Init(LCD_CTRL, &PinCfg);

		PinCfg.GPIO_PinNumber = Rw_Switch;
		PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
		PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
		MCAL_GPIO_Init(LCD_CTRL, &PinCfg);

		PinCfg.GPIO_PinNumber = EN_Switch;
		PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
		PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
		MCAL_GPIO_Init(LCD_CTRL, &PinCfg);



		//	DataDir_LCD_CTRL |= (1 << EN_SWITCH | 1 << RS_SWITCH | 1 << RW_SWITCH);
		MCAL_GPIO_WritePin(LCD_CTRL, EN_Switch, GPIO_PIN_RESET);
		MCAL_GPIO_WritePin(LCD_CTRL, RS_Switch, GPIO_PIN_RESET);
		MCAL_GPIO_WritePin(LCD_CTRL, Rw_Switch, GPIO_PIN_RESET);

	//LCD_CTRL &=~((1<<EN_Switch)|(1<<Rw_Switch)|(1<<RS_Switch));

	wait_ms(20);

	//DataDir_LCD_PORT = 0xff;
	LCD_DataDir_Output();

	LCD_clear_screen();
	LCD_WRITE_COMMAND(LCD_Function_8BIT_2LINE);


	LCD_WRITE_COMMAND(LCD_Entry_Mode);
	LCD_WRITE_COMMAND(LCD_Display_ON_Cursor_ON);

}

void LCD_WRITE_COMMAND(unsigned char command){

//	LCD_IS_BUSY();
	//LCD_PORT = command;
	MCAL_GPIO_WritePort_8(LCD_PORT,command);
//	MCAL_GPIO_WritePort(LCD_CTRL,command);

	MCAL_GPIO_WritePin(LCD_CTRL, RS_Switch, GPIO_PIN_RESET);
	MCAL_GPIO_WritePin(LCD_CTRL, Rw_Switch, GPIO_PIN_RESET);
//	LCD_CTRL &=~((1<<Rw_Switch)|(1<<RS_Switch));
	wait_ms(1);
	LCD_KICK();

}
void LCD_WRITE_CHAR(unsigned char data){

//	LCD_IS_BUSY();
//	LCD_PORT = data;
	MCAL_GPIO_WritePort_8(LCD_PORT,data);
//	MCAL_GPIO_WritePort(LCD_PORT,data);
//	LCD_CTRL &=~((1<<Rw_Switch));
	MCAL_GPIO_WritePin(LCD_CTRL, RS_Switch, GPIO_PIN_SET);
	MCAL_GPIO_WritePin(LCD_CTRL, Rw_Switch, GPIO_PIN_RESET);





	wait_ms(1);
	LCD_KICK();

//	if(++curr_pos >= 16);
//	LCD_GOTO_XY(2,0);
}
void LCD_WRITE_STR(char* string){
	int count =0;
	while(*string){

		count++;
		if(count==16)
			LCD_GOTO_XY(2,0);
		else if(count ==32)
		{
			LCD_clear_screen();
			LCD_GOTO_XY(1,0);
			count =0;
		}
		LCD_WRITE_CHAR(*string++);
	}
}
void LCD_IS_BUSY(void){

	//DataDir_LCD_PORT = 0x00;
	LCD_DataDir_Input();

	MCAL_GPIO_WritePin(LCD_CTRL, Rw_Switch, GPIO_PIN_SET);
	MCAL_GPIO_WritePin(LCD_CTRL, RS_Switch, GPIO_PIN_RESET);
	//LCD_CTRL |=(1<<Rw_Switch); //read mode
	//LCD_CTRL &= ~(1<<RS_Switch);
	 LCD_KICK();

	 MCAL_GPIO_WritePin(LCD_CTRL, Rw_Switch, GPIO_PIN_RESET);
	 //LCD_CTRL &= ~(1<<Rw_Switch);
}

