/*
 * util.h
 *
 *	Provides basic utility function such as delay and 
 *	value mapping
 *
 * Created on: May 30th, 2023
 *		Author: Jackie Huynh
 *
 */
 

#ifndef UTIL_H_
#define UTIL_H_

#include <stdint.h>

#define CONSTANT_FILL	(50)     // a place holder for all constants needs to be defined by students
#define CODE_FILL	(0)     // a place holder for code needs to be defined by students

/* List of Fill In Macros */
#define EN_WTIMER0_CLOCK			SYSCTL_RCGCWTIMER_R0
#define WTIMER0_TAEN_BIT			0x01
#define WTIMER0_32_BIT_CFG		0x04
#define WTIMER0_PERIOD_MODE		0x02
#define PRESCALER_VALUE				16000

void WTIMER0_Init(void);
void DELAY_1MS(uint32_t);
int16_t map(int16_t, int16_t, int16_t, int16_t, int16_t);

#endif