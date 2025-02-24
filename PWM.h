// PWM.h
// Runs on TM4C123
// Use PWM0/PB6 and PWM1/PB7 to generate pulse-width modulated outputs.
// Daniel Valvano
// March 28, 2014

/* This example accompanies the book
   "Embedded Systems: Real Time Interfacing to ARM Cortex M Microcontrollers",
   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2014
  Program 6.7, section 6.3.2

 Copyright 2014 by Jonathan W. Valvano, valvano@mail.utexas.edu
    You may use, edit, run or distribute this file
    as long as the above copyright notice remains
 THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 VALVANO SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 For more information about my classes, my research, and my books, see
 http://users.ece.utexas.edu/~valvano/
 */
// Modified by Min He, September 7, 2021
#include <stdint.h>

#define DIRECTION (*((volatile unsigned long *)0x40005330))
// 11001100 = 0xCC
// right motor pins 7,6 // left motor pins 3,2
#define FORWARD 			0xCC 	//11001100
#define BACKWARD 			0x88  //10001000
#define PIVOT_LEFT		0xC8	//11001000 right forward, left backward
#define PIVOT_RIGHT 	0x8C	//10001100 right backward, left forward

#define LIGHT (*((volatile unsigned long *)0x40025038))
#define RED 0x02
#define GREEN 0x08
#define BLUE 0x04

#define STOP 1
#define SPEED_30 3000
#define SPEED_35 3500
#define SPEED_50 5000
#define SPEED_60 6000
#define SPEED_80 8000
#define SPEED_98 9800

#define PWMA 0x10 // left motor PB4 = 0x10, DIR=PB2 SLP=PB3
#define PWMB 0x20 // right motor PB5 = 0x20, DIR=PB6 SLP=PB7
// PWM	 0x30
// direction pins
// PB7,6,3,2 = 11001100 = 0xCC
#define DIR_MASK 0xCC

int done;

void PLL_Init(void);

// period is 16-bit number of PWM clock cycles in one period 
// Output on PB6/M0PWM0
void PWM0GEN1A_Init(uint16_t period);

// change duty cycle of PB6
// duty is number of PWM clock cycles output is high  
void PWM0A_Duty(uint16_t duty);

// period is 16-bit number of PWM clock cycles in one period 
// Output on PB7/M0PWM1
void PWM0GEN1B_Init(uint16_t period);

// change duty cycle of PB7
// duty is number of PWM clock cycles output is high  
void PWM0B_Duty(uint16_t duty);

void PortB_Init(void);
void SwitchLED_Init(void);




