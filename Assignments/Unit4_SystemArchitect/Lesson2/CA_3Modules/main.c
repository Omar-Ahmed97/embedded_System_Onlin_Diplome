/*
 * main.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Omar
 */


#include "CA.h"
#include "US.h"
#include "DC.h"

void setup()
{
	//init all the driver
	//init IRQ ....
	//init HAL US_Driver DC_Driver
	//init Block
	US_init();
	DC_init();
	//set states pointer for each block
	CA_state = STATE_(CA_waiting);
	DC_state = STATE_(DC_idle);
	US_state = STATE_(US_busy);
}

int main()
{
	setup();

	while(1)
	{
		//call state for each block
		US_state();
		CA_state();
		DC_state();
	}
return 0;
}
