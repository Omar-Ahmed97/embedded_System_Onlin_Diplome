/*
 * AlarmMonitor.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: Omar
 */

#ifndef ALARMMONITOR_H_
#define ALARMMONITOR_H_

#include"State.h"
//define state

enum{

	Alarm_Monitor_AlarmON,
	Alarm_Monitor_AlarmOFF

}Alarm_Monitor_state_id;




STATE_define(Alarm_Monitor_AlarmON);
STATE_define(Alarm_Monitor_AlarmOFF);

extern void(*Alarm_Monitor_state)();

#endif /* ALARMMONITOR_H_ */
