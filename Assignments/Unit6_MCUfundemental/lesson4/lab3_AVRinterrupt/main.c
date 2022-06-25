/*
 * main.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Omar
 */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int main(){

	MCUCR |= (1<<ISC00);		//Any logical change on INT0 generates an interrupt request.
	MCUCR |= (1<<ISC11)|(1<<ISC10);		//The  rising edge of INT1 generates an interrupt request
	MCUCSR &= ~(1<<ISC2);		// ISC2 is written to one, a falling edge on INT2 activates the interrupt

	GICR |= (1<<7)|(1<<6)|(1<<5); //Enable interrupt INT0 ,INT2 ,INT2

	SREG |=(1<<7);				//Enable Global interrupt

	DDRD |=(1<<7)|(1<<6)|(1<<5);   // PINsD 7,6,5 Output

	while(1){
		PORTD &= ~((1<<5) | (1<<6) | (1<<7)) ;
		_delay_ms(1000);
	}
}
ISR(INT0_vect){

	PORTD |= 1<<5;
	_delay_ms(1000);
}
ISR(INT1_vect){
	PORTD |= 1<<6;
	_delay_ms(1000);

}
ISR(INT2_vect){
	PORTD |= 1<<7 ;
	_delay_ms(1000);

}
