/*
 * Pressur_Sensor_Driver.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Omar
 */


#include "Pressur_Sensor_Driver.h"

int pVal;
void(*Pressure_Sensor_Driver_state)();

void Pressure_Sensor_Driver_init()
{
//init Pressure_Sensor_Driver_state Driver


}

STATE_define(Pressure_Sensor_Driver_reading)
{
	//name of state
	Pressure_Sensor_Driver_state_id = Pressure_Sensor_Driver_reading;
	//reading pressure value
	pVal = getPressureVal();
	//send pressure value
	set_pVal(pVal);


	Pressure_Sensor_Driver_state = STATE(Pressure_Sensor_Driver_waiting);

	}

STATE_define(Pressure_Sensor_Driver_waiting)
{
	//name of state
		Pressure_Sensor_Driver_state_id = Pressure_Sensor_Driver_waiting;
	//Delay
	Delay(100);

	Pressure_Sensor_Driver_state= STATE(Pressure_Sensor_Driver_reading);
	}
