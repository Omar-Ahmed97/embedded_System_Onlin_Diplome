/*
 * main.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Omar
 */

#include <avr/io.h>
#include "lcd.h"

int main()
{
	LCD_INIT();
	KEYPAD_INIT();
	char ch;
//	LCD_WRITE_CHAR('A');
//	LCD_WRITE_STR("omar Ahmed oooooooooooooooo");
	while(1){
		 ch = KEYPAD_GETCHAR();
		 if(ch != 'n'){
		LCD_WRITE_CHAR(ch);
		 }
	}

return 0;
}
