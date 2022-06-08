/*
 * CA.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Omar
 */
#include"CA.h"

// variable
int CA_speed =0;
int CA_distance =0;
int CA_tjreshold =50;

void(*CA_state)();

//state pointer to function



void US_Set_distance(int d)
{
	CA_distance = d;
	(CA_distance <= CA_tjreshold) ? (CA_state = STATE_(CA_waiting)) : (CA_state =  STATE_(CA_driving));
	printf("US--------distance = %d---------\n",CA_distance);

}
STATE_define(CA_waiting)
{
	//State name

	CA_state_id = CA_waiting;
	printf("CA_waiting State: distance = %d Speed = %d \n ",CA_distance,CA_speed);
	//state Action
	CA_speed =0;
	 DC_motor(CA_speed);
	//DC _Motor speed

}

STATE_define(CA_driving)
{
	//State name

	CA_state_id = CA_driving;
	printf("CA_driving State: distance = %d Speed = %d \n ",CA_distance,CA_speed);
	//state Action
	CA_speed =30;
	//DC _Motor speed
	 DC_motor(CA_speed);



}

