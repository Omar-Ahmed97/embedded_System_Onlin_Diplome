/*
 * US.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Omar
 */
#include"US.h"

// variable

int US_distance =0;


void(*US_state)();

//state pointer to function

int US_Get_distance_random(int l , int r, int count);
void US_init()
{
//init US Driver
	printf("US_init \n");

}

STATE_define(US_busy)
{
	//State name

	US_state_id = US_busy;
	//state Action

	//ultra sonic get distance
		US_distance = US_Get_distance_random(45 , 55 ,  1);

	printf("US_waiting State: distance = %d  \n ",US_distance);
	US_Set_distance(US_distance);

	US_state = STATE_(US_busy);

}

int US_Get_distance_random(int l , int r, int count)
{


	int i;
	for(i=0;i<count;i++){
		int rand_num = (rand()% (r-l+1)) + l;
			return rand_num;
	}

}
