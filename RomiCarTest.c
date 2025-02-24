// PWMtest.c
// Runs on TM4C123
// Use PWM0/PB6 and PWM1/PB7 to generate pulse-width modulated outputs.
// Min He
// September 7, 2021

// This is an example program to show how to use hardware PWM on TM4C123.
#include <stdint.h>
#include "PWM.h"
#include "PLL.h"
#include "SysTick.h"
#include "tm4c123gh6pm.h"

//#define DIRECTION (*((volatile unsigned long *)0x4002403C)) // Mask for PE0-3
//#define FORWARD 		0x0F		// 1111
//#define BACKWARD 		0x0A		// 1010
//#define DIRECTION (*((volatile unsigned long *)0x40005330))
//#define FORWARD 			0xCC 	//11001100
//#define BACKWARD 			0x88  //10001000

#define PERIOD 10000				// Total PWM period
//#define STEP 1000						// increments of duty cycle
//#define MAX_DUTY 9000				// max duty cycle (90%)
//#define STOP 1							// min duty cycle (0%)
//#define SPEED_35 3500				// 35% duty cycle
//#define SPEED_60 6000				// 60% duty cycle
//#define SPEED_80 8000				// 80% duty cycle
//#define SPEED_98 9800				// 98% duty cycle


void Delay(void);
extern void DisableInterrupts(void); // Disable interrupts
extern void EnableInterrupts(void);  // Enable interrupts
extern void WaitForInterrupt(void);  // low power mode
extern void PortFHandler(void);

int main(void){
	
 	DisableInterrupts();
	PLL_Init();									// 50MHz system clock
	PortB_Init();								// initialize PE0-3, direction - PE0&1 for R, PE2&3 for L
  PWM0GEN1A_Init(PERIOD);         // initialize PWM0, PB6 LEFT MOTOR
  PWM0GEN1B_Init(PERIOD);         // initialize PWM0, PB7 RIGHT MOTOR
	
	SwitchLED_Init();							// switches controls car direction, LEDs indicates car direction
	EnableInterrupts();
	
	DIRECTION = FORWARD;
	PWM0A_Duty(STOP);
	PWM0B_Duty(STOP);
	
	
	done = 0;
	
	while(1){
		WaitForInterrupt();
		if (!done)
		{
			GPIO_PORTF_ICR_R = 0x10;  // acknowledge flag4
			// forward 50
			DIRECTION = FORWARD;
			PWM0A_Duty(SPEED_50);
			PWM0B_Duty(SPEED_50);
			SysTick_Wait(16);
			// delay to prevent stalling
			PWM0A_Duty(STOP);
			PWM0B_Duty(STOP);
			SysTick_Wait(4);
			// backward 50
			DIRECTION = BACKWARD;
			PWM0A_Duty(SPEED_50);
			PWM0B_Duty(SPEED_50);
			SysTick_Wait(16);// delay to prevent stalling
			PWM0A_Duty(STOP);
			PWM0B_Duty(STOP);
			SysTick_Wait(4);
			// forward left 20 diff
			DIRECTION = FORWARD;
			PWM0A_Duty(SPEED_50);
			PWM0B_Duty(SPEED_30);
			SysTick_Wait(16);// delay to prevent stalling
			PWM0A_Duty(STOP);
			PWM0B_Duty(STOP);
			SysTick_Wait(4);
			// forward right 20 diff
			PWM0A_Duty(SPEED_30);
			PWM0B_Duty(SPEED_50);
			SysTick_Wait(16);// delay to prevent stalling
			PWM0A_Duty(STOP);
			PWM0B_Duty(STOP);
			SysTick_Wait(4);
			// backward left 20 diff
			DIRECTION = BACKWARD;
			PWM0A_Duty(SPEED_30);
			PWM0B_Duty(SPEED_50);
			SysTick_Wait(16);// delay to prevent stalling
			PWM0A_Duty(STOP);
			PWM0B_Duty(STOP);
			SysTick_Wait(4);
			// backward right 20 diff
			PWM0A_Duty(SPEED_50);
			PWM0B_Duty(SPEED_30);
			SysTick_Wait(16);// delay to prevent stalling
			PWM0A_Duty(STOP);
			PWM0B_Duty(STOP);
			SysTick_Wait(4);
			// pivot left
			DIRECTION = PIVOT_LEFT;
			PWM0A_Duty(SPEED_50);
			PWM0B_Duty(SPEED_50);
			SysTick_Wait(16);// delay to prevent stalling
			PWM0A_Duty(STOP);
			PWM0B_Duty(STOP);
			SysTick_Wait(4);
			// pivot right
			DIRECTION = PIVOT_RIGHT;
			PWM0A_Duty(SPEED_50);
			PWM0B_Duty(SPEED_50);
			SysTick_Wait(16);// delay to prevent stalling
			PWM0A_Duty(STOP);
			PWM0B_Duty(STOP);
			SysTick_Wait(4);
			// reset
			DIRECTION = FORWARD;
			PWM0A_Duty(STOP);
			PWM0B_Duty(STOP);
		}
		done = 0;
  }
}

// Subroutine to wait 0.5 sec
// Inputs: None
// Outputs: None
// Notes: ...
//void Delay(void){unsigned long volatile time;
//  time = 727240*100/91;  // 1 sec
//  while(time){
//		time--;
//  }
//	for (time=0;time<1000;time=time+10) {
//	}
//}
