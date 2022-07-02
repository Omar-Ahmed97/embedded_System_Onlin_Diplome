/*
 * keypad_driver.c
 *
 *  Created on: ٠٢‏/٠٧‏/٢٠٢٢
 *      Author: Omar
 */



#include "../../stm32_F103C6_drivers/inc/KeyPad.h"

GPIO_PinConfig_t PinCfg;

int KeyPad_R[] = {R0,R1,R2,R3};
int KeyPad_C[] = {C0,C1,C2,C3};


void KEYPAD_DataDir_Output(){
	///GPIO_PIN_4 (output PUSH pull Mode)
	//01: Output mode, max speed 10 MHz.
	PinCfg.GPIO_PinNumber = R0;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(KEYPAD_PORT, &PinCfg);

	///GPIO_PIN_5 (output PUSH pull Mode)
	//01: Output mode, max speed 10 MHz.
	PinCfg.GPIO_PinNumber = R1;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(KEYPAD_PORT, &PinCfg);

	///GPIO_PIN_6 (output PUSH pull Mode)
	//01: Output mode, max speed 10 MHz.
	PinCfg.GPIO_PinNumber = R2;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(KEYPAD_PORT, &PinCfg);

	///GPIO_PIN_7 (output PUSH pull Mode)
	//01: Output mode, max speed 10 MHz.
	PinCfg.GPIO_PinNumber = R3;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(KEYPAD_PORT, &PinCfg);



	///GPIO_PIN_4 (output PUSH pull Mode)
	//01: Output mode, max speed 10 MHz.
	PinCfg.GPIO_PinNumber = C0;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(KEYPAD_PORT, &PinCfg);

	///GPIO_PIN_5 (output PUSH pull Mode)
	//01: Output mode, max speed 10 MHz.
	PinCfg.GPIO_PinNumber = C1;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(KEYPAD_PORT, &PinCfg);

	///GPIO_PIN_6 (output PUSH pull Mode)
	//01: Output mode, max speed 10 MHz.
	PinCfg.GPIO_PinNumber = C2;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(KEYPAD_PORT, &PinCfg);

	///GPIO_PIN_7 (output PUSH pull Mode)
	//01: Output mode, max speed 10 MHz.
	PinCfg.GPIO_PinNumber = C3;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(KEYPAD_PORT, &PinCfg);
}



void KEYPAD_INIT()
{
	//DataDir_KEYPAD_PORT &=~((1<<R0)|(1<<R1)|(1<<R2)|(1<<R3));
	//DataDir_KEYPAD_PORT |=((1<<C0)|(1<<C1)|(1<<C2)|(1<<C3));
	KEYPAD_DataDir_Output();


	//KEYPAD_PORT = 0xff;
	MCAL_GPIO_WritePort(KEYPAD_PORT, 0xFF);
}
char KEYPAD_GETCHAR(){
	int i,j;
	for(i = 0 ; i <4;i++){
		//KEYPAD_PORT |=((1<<C0)|(1<<C1)|(1<<C2)|(1<<C3));
		MCAL_GPIO_WritePin(KEYPAD_PORT, C0, GPIO_PIN_SET);
		MCAL_GPIO_WritePin(KEYPAD_PORT, C1, GPIO_PIN_SET);
		MCAL_GPIO_WritePin(KEYPAD_PORT, C2, GPIO_PIN_SET);
		MCAL_GPIO_WritePin(KEYPAD_PORT, C3, GPIO_PIN_SET);

		//KEYPAD_PORT &=~(1<<KeyPad_C[i]);
		MCAL_GPIO_WritePin(KEYPAD_PORT,KeyPad_C[i], GPIO_PIN_RESET);

		for(j=0;j<4;j++){

			if((MCAL_GPIO_ReadPin(KEYPAD_PORT, KeyPad_R[j])) == 0){
				while((MCAL_GPIO_ReadPin(KEYPAD_PORT, KeyPad_R[j]))== 0);
				switch(i){
				case 0:{
					if( j ==0 ) return '7';
					if( j ==1 ) return '4';
					if( j ==2 ) return '1';
					if( j ==3 ) return '#';
					break;
				}
				case 1:{
					if( j ==0 ) return '8';
					if( j ==1 ) return '5';
					if( j ==2 ) return '2';
					if( j ==3 ) return '0';
					break;
				}
				case 2:{
					if( j ==0 ) return '9';
					if( j ==1 ) return '6';
					if( j ==2 ) return '3';
					if( j ==3 ) return '=';
					break;
				}
				case 3:{
					if( j ==0 ) return '/';
					if( j ==1 ) return '*';
					if( j ==2 ) return '-';
					if( j ==3 ) return '+';
					break;
				}

				}
			}
		}
	}
	return 'n';
}

