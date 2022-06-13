/*
 * Main_Alg.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Omar
 */

#include "Main_Alg.h"



void set_pVal(int pVal){
	if(pVal > threShold)
		High_Pressure_Detection(1);
	else  High_Pressure_Detection(0);

}
