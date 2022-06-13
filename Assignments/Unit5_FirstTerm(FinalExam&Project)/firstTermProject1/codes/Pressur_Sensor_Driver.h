/*
 * Pressur_Sensor_Driver.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: Omar
 */

#ifndef PRESSUR_SENSOR_DRIVER_H_
#define PRESSUR_SENSOR_DRIVER_H_

#include"State.h"
//define state

enum{

	Pressure_Sensor_Driver_reading,
	Pressure_Sensor_Driver_waiting

}Pressure_Sensor_Driver_state_id;



void Pressure_Sensor_Driver_init();
STATE_define(Pressure_Sensor_Driver_reading);
STATE_define(Pressure_Sensor_Driver_waiting);

extern void(*Pressure_Sensor_Driver_state)();

#endif /* PRESSUR_SENSOR_DRIVER_H_ */
