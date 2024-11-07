/*
 * Servo.h
 *
 *	Provides functions to interact with a standard angular Servo Motor
 *
 * Created on: June 11th, 2023
 *		Author: Jackie Huynh
 *
 */
 
 
#ifndef SERVO_H_
#define SERVO_H_

#include <stdint.h>
#include "util.h"

// USE HARDWARE PWM MODULE 0 GEN 0 CHANNEL 0 PB6

/* List of Fill In Macros */
#define EN_PWM0_GPIOB_CLOCK		SYSCTL_RCGC2_GPIOB   // Port B Clock Gating Control: 0x00000002
#define PWM0_PIN							0x40                 // PB6 Binary: 0x01000000
#define CLEAR_ALT_FUNCTION		GPIO_PCTL_PB6_M      // ^PB6 Binary: 0x0F000000
#define PWM0_ALT_FUNCTION			GPIO_PCTL_PB6_M0PWM0 // M0PWM0 on PB6: 0x04000000
#define EN_PWM0_CLOCK					SYSCTL_RCGCPWM_R0    // PWM Module 0 Run Mode Clock, Gating Control: 0x00000001
#define EN_USE_PWM_DIV				SYSCTL_RCC_USEPWMDIV // Enable PWM Clock Divisor: 0x00100000
#define CLEAR_PWM_DIV					SYSCTL_RCC_PWMDIV_M  // Clear any previous PWM divider values 0x000E0000
#define PWM0_DIV_VALUE				SYSCTL_RCC_PWMDIV_8  // set divider to 8: 0x00040000
#define PWM0_DEFAULT_CONFIG		0         			  	 // track exlorer: PWM0_1_CTL_R = 0;
#define PWM0_GEN_CONFIG				0xC8        				 // 347 PWM Lecture 2 pg 32
#define PWM0_COUNTER					40000       				 // 50Hz reload value: 20ms / 0.5us = 40000
#define PWM0_START						0x01        				 // 347 PWM Lecture 2 pg 35
#define EN_PWM0_FUNCTION			0x01        				 // 347 PWM Lecture 2 pg 36

/* 0.5ms (2.5%) - 2.5ms (12.5%) Duty Cycle */
/* Effective PWM clk: 16MHz/8 prescaler = 2MHz */
/* PWM tick period: 1/2MHz = 0.5us */
/* Period = Counter * Time Per Tick */
/* Counter = Period / Time Per Tick = 20ms / 0.5us = 40000 */
/* Frequency = 1 / Period = 1 / 20ms = 50Hz */
#define SERVO_MIN_CNT					1000 // 0.5ms/0.5us = 1000
#define SERVO_MAX_CNT					5000 // 2.5ms/0.5us = 5000

/* Max Range of Either -90 to 90 or 0 to 180 */
#define SERVO_MIN_ANGLE				-90 // ^Minimum angle
#define SERVO_MAX_ANGLE	      90  // ^Maximum angle

/*
 *	-------------------Servo_Init------------------
 *	Basic Servo Initialization function for PWM Generation
 *	Input: None
 *	Output: None
 */
void Servo_Init(void);

/*
 *	-------------------Drive_Servo------------------
 *	Drives the Servo Motor to a specified angle
 *	Input: Desired Angle
 *	Output: None
 */
void Drive_Servo(int16_t angle);

#endif