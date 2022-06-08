/*
 * US.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: Omar
 */

#ifndef US_H_
#define US_H_

#include"state.h"
//define state

enum{

	US_busy

}US_state_id;



//declare states function US
STATE_define(US_busy);


//state pointer to function
extern void(*US_state)();

void US_init();
#endif /* US_H_ */
