/*
 * AlarmMonitor.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Omar
 */



#include "AlarmMonitor.h"



void(*Alarm_Monitor_state)();

void High_Pressure_Detection(int highDetected)
{
	if(highDetected)
		Alarm_Monitor_state = STATE(Alarm_Monitor_AlarmON);
	else Alarm_Monitor_state=STATE(Alarm_Monitor_AlarmOFF);

	}

STATE_define(Alarm_Monitor_AlarmON)
{
	//name of state
	Alarm_Monitor_state_id = Alarm_Monitor_AlarmON;
	//send high signal to start Alarm
	start_Alarm();
	//Delay
	Delay(500);
	//stop Alarm
	stop_Alarm();

	Alarm_Monitor_state=STATE(Alarm_Monitor_AlarmOFF);

	}

STATE_define(Alarm_Monitor_AlarmOFF)
{
	//name of state
	Alarm_Monitor_state_id = Alarm_Monitor_AlarmOFF;
	//stop Alarm
	stop_Alarm();

	}
