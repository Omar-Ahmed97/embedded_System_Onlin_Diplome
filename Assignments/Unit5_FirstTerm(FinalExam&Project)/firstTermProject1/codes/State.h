/*
 * State.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: Omar
 */

#ifndef STATE_H_
#define STATE_H_


#include "stdio.h"
#include "stdlib.h"

//Automatic state function generated
#define STATE_define(_StateFUN_)  void ST_##_StateFUN_()
#define STATE(_StateFUN_) ST_##_StateFUN_

//connection
void set_pVal(int pVal);
void start_Alarm();
void stop_Alarm();
void High_Pressure_Detection(int highDetected);

#endif /* STATE_H_ */
