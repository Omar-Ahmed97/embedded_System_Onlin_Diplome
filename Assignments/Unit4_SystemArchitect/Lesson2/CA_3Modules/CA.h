/*
 * CA.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: Omar
 */

#ifndef CA_H_
#define CA_H_

#include"state.h"
//define state

enum{
	CA_waiting,CA_driving
}CA_state_id;




//declare states function CA
STATE_define(CA_waiting);
STATE_define(CA_driving);

//state pointer to function
extern void(*CA_state)();

#endif /* CA_H_ */
