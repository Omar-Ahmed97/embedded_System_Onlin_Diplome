/*
 * DC.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: Omar
 */

#ifndef DC_H_
#define DC_H_

#include"state.h"
//define state

enum{

	DC_idle,
	DC_busy

}DC_state_id;



//declare states function DC
STATE_define(DC_idle);
STATE_define(DC_busy);

//state pointer to function
extern void(*DC_state)();

#endif /* DC_H_ */
