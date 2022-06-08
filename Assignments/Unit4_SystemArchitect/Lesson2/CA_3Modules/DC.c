/*
 * DC.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Omar
 */
#include"DC.h"

// variable
int DC_speed =0;


void(*DC_state)();

//state pointer to function


void DC_init()
{
 //init pwm
	printf("DC INIT");
}
void DC_motor(int S)
{
DC_speed =0;
DC_state = STATE_(DC_busy);
printf("DC--------speed = %d---------\n",DC_speed);
}
STATE_define(DC_idle)
{
	//State name

	DC_state_id = DC_idle;
	//state Action
	//call pwm =DC_Speed	DC_speed =0;
	//DC _Motor speed
	//ultra sonic get distance


	printf("DC_idle State:  Speed = %d \n ",DC_speed);

}

STATE_define(DC_busy)
{
	//State name

	DC_state_id = DC_busy;
	//state Action
	DC_speed =30;
	//DC _Motor speed


	DC_state = STATE_(DC_idle);
	printf("DC_idle State:  Speed = %d \n ",DC_speed);
}

