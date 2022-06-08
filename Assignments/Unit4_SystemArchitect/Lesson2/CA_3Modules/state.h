/*
 * state.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: Omar
 */

#ifndef STATE_H_
#define STATE_H_

#include "stdio.h"
#include "stdlib.h"
//Automatic STATE Function generated
#define STATE_define(_stateFUN_) void ST_##_stateFUN_()
#define STATE_(_stateFUN_) ST_##_stateFUN_

//state connection

void US_Set_distance(int d);
void DC_motor(int S);

#endif /* STATE_H_ */
