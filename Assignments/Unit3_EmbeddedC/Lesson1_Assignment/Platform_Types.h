/*
 * Platform_Types.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: Omar
 */

#ifndef PLATFORM_TYPES_H_
#define PLATFORM_TYPES_H_

typedef unsigned char boolean;

typedef signed char 	   sint8_t;
typedef unsigned char	   uint8_t;
typedef signed short 	   sint16_t;
typedef unsigned short 	   uint16_t;
typedef signed long 	   sint32_t;
typedef unsigned long 	   uint32_t;
typedef signed long long   sint64_t;
typedef unsigned long long uint64_t;



typedef float 		   float32_t;
typedef double		   float64_t;

typedef volatile sint8_t   vint8;
typedef volatile uint8_t   vuint8;
typedef volatile sint16_t  vint16;
typedef volatile uint16_t  vuint16;
typedef volatile sint32_t  vint32;
typedef volatile uint32_t  vuint32;
typedef volatile sint64_t  vint64;
typedef volatile uint64_t  vuint64;

typedef volatile float32_t vfloat32_t;
typedef volatile float64_t vfloat64_t;


#endif /* PLATFORM_TYPES_H_ */
