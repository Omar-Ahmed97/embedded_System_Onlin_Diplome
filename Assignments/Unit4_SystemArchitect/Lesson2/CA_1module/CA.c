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

int US_Get_distance_random(int l , int r, int count);

STATE_define(CA_waiting)
{
	//State name

	CA_state_id = CA_waiting;
	//state Action
	CA_speed =0;
	//DC _Motor speed
	//ultra sonic get distance
	CA_distance = US_Get_distance_random(45 , 55 ,  1);

	//Event Action
	(CA_distance <= CA_tjreshold) ? (CA_state = STATE_(CA_waiting)) : (CA_state =  STATE_(CA_driving));
	printf("CA_waiting State: distance = %d Speed = %d \n ",CA_distance,CA_speed);

}

STATE_define(CA_driving)
{
	//State name

	CA_state_id = CA_driving;
	//state Action
	CA_speed =30;
	//DC _Motor speed
	//ultra sonic get distance
	CA_distance = US_Get_distance_random(45 , 55 ,  1);
	//Event Action
	(CA_distance <= CA_tjreshold)?(CA_state = STATE_(CA_waiting)) : (CA_state = STATE_(CA_driving));
	printf("CA_driving State: distance = %d Speed = %d \n ",CA_distance,CA_speed);

}

int US_Get_distance_random(int l , int r, int count)
{


	int i;
	for(i=0;i<count;i++){
		int rand_num = (rand()% (r-l+1)) + l;
			return rand_num;
	}

}
