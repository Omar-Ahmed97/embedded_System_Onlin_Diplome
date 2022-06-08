/*
 * main.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Omar
 */


#include "CA.h"

void setup()
{
	//init all the driver
	//init IRQ ....
	//init HAL US_Driver DC_Driver
	//init Block
	//set states pointer for each block
	CA_state = STATE_(CA_waiting);
}

int main()
{
	setup();

	while(1)
	{
		//call state for each block
		CA_state();
	}
return 0;
}
