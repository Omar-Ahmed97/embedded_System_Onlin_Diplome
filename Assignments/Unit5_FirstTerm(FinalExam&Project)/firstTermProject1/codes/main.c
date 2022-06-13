/*
 * main.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Omar
 */

#include "driver.h"
#include "Alarm_Actuator_Driver.h"
#include "AlarmMonitor.h"
#include "Main_Alg.h"
#include "Pressur_Sensor_Driver.h"


void setup()
{
	//init all the driver
	//init IRQ ....
	//init HAL US_Driver DC_Driver
	//init Block
	GPIO_INITIALIZATION ();
	//set states pointer for each block
	Alarm_Monitor_state = STATE(Alarm_Monitor_AlarmOFF);
	Pressure_Sensor_Driver_state = STATE(Pressure_Sensor_Driver_reading);

}

int main()
{
	setup();

	while(1)
	{
		//call state for each block
		Pressure_Sensor_Driver_state();
		Alarm_Monitor_state();

	}
return 0;
}
