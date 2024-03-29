// ADCSWTrigger.c
// Runs on LM4F120/TM4C123
// Provide functions that sample ADC inputs PE4, PE5 using SS2
// to be triggered by software and trigger two conversions,
// wait for them to finish, and return the two results.
// Daniel Valvano
// May 2, 2015

/* This example accompanies the book
   "Embedded Systems: Real Time Interfacing to ARM Cortex M Microcontrollers",
   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2015

 Copyright 2015 by Jonathan W. Valvano, valvano@mail.utexas.edu
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
#include <stdint.h>
#include "ADC_Joystick.h"
#include "../inc/tm4c123gh6pm.h"
#include "ST7735.h"
#include <stdbool.h>

uint32_t joystickData[2];

bool PE3_Debounced = true;
bool PE2_Debounced = true;


void ADC_Init89(void){ 
  volatile uint32_t delay;                         
//  SYSCTL_RCGC0_R |= 0x00010000; // 1) activate ADC0 (legacy code)
  SYSCTL_RCGCADC_R |= 0x00000001; // 1) activate ADC0
  SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R4; // 1) activate clock for Port E
  delay = SYSCTL_RCGCGPIO_R;      // 2) allow time for clock to stabilize
  delay = SYSCTL_RCGCGPIO_R;
	delay++;
	delay++;
  GPIO_PORTE_DIR_R &= ~0x3C;      // 3) make PE4 PE5 input (also make PE2 and PE3 inputs)
  GPIO_PORTE_AFSEL_R |= 0x30;     // 4) enable alternate function on PE4 PE5
  GPIO_PORTE_DEN_R &= ~0x30;      // 5) disable digital I/O on PE4 PE5
	GPIO_PORTE_DEN_R |= 0x0C;				// enable digital I/O on PE2 and PE3

  GPIO_PORTE_DIR_R &= ~0x30;      // 3) make PE4 PE5 input
  GPIO_PORTE_AFSEL_R |= 0x30;     // 4) enable alternate function on PE4 PE5
  GPIO_PORTE_DEN_R &= ~0x30;      // 5) disable digital I/O on PE4 PE5
                                  // 5a) configure PE4 as ?? (skip this line because PCTL is for digital only)
  GPIO_PORTE_PCTL_R = GPIO_PORTE_PCTL_R&0xFF00FFFF;
  GPIO_PORTE_AMSEL_R |= 0x30;     // 6) enable analog functionality on PE4 PE5
  ADC0_PC_R &= ~0xF;              // 8) clear max sample rate field
  ADC0_PC_R |= 0x1;               //    configure for 125K samples/sec
  ADC0_SSPRI_R = 0x3210;          // 9) Sequencer 3 is lowest priority
  ADC0_ACTSS_R &= ~0x0004;        // 10) disable sample sequencer 2
  ADC0_EMUX_R &= ~0x0F00;         // 11) seq2 is software trigger
  ADC0_SSMUX2_R = 0x0089;         // 12) set channels for SS2
  ADC0_SSCTL2_R = 0x0060;         // 13) no TS0 D0 IE0 END0 TS1 D1, yes IE1 END1
  ADC0_IM_R &= ~0x0004;           // 14) disable SS2 interrupts
  ADC0_ACTSS_R |= 0x0004;         // 15) enable sample sequencer 2
	ADCStatus = 0;
}

//------------ADC_In89------------
// Busy-wait Analog to digital conversion
// Input: none
// Output: two 12-bit result of ADC conversions
// Samples ADC8 and ADC9 
// 125k max sampling
// software trigger, busy-wait sampling
// data returned by reference
// data[0] is ADC8 (PE5) 0 to 4095
// data[1] is ADC9 (PE4) 0 to 4095
void ADC_In89(uint32_t data[2]){ 
  ADC0_PSSI_R = 0x0004;            // 1) initiate SS2
  while((ADC0_RIS_R&0x04)==0){};   // 2) wait for conversion done
  data[1] = ADC0_SSFIFO2_R&0xFFF;  // 3A) read first result
  data[0] = ADC0_SSFIFO2_R&0xFFF;  // 3B) read second result
  ADC0_ISC_R = 0x0004;             // 4) acknowledge completion
}

void SysTick_Init(void){
	NVIC_ST_CTRL_R = 0; // disable systick during setup
	NVIC_ST_RELOAD_R = 0x00DFFFFF; // set reload to max value
	NVIC_ST_CURRENT_R = 0; // clears current
	NVIC_ST_CTRL_R = 0x07; // enable systick with core clock
}

void SysTick_Handler(void){
	ADC_In89(joystickData); 
	ADCStatus = 1;
}

uint32_t getJoystickX(void){
	if(joystickData[1] < 300){
		return 0; // left
	}
	else if(joystickData[1] > 3700){
		return 2; // right
	}
	else{
		return 1; // center
	}
}

uint32_t getJoystickY(void){
	if(joystickData[0] < 300){
		return 0; // up
	}
	else if(joystickData[0] > 3700){
		return 2; // down
	}
	else{
		return 1; // center
	}
}

bool isPE2Pressed(void){
	if((GPIO_PORTE_DATA_R & 0x04) == 0){
		PE2_Debounced = true;
		return false;
	}
	else{
		if(!PE2_Debounced) return false;
		PE2_Debounced = false;
		return true;
	}
}

bool isPE3Pressed(void){
	if((GPIO_PORTE_DATA_R & 0x08) == 0){
		PE3_Debounced = true;
		return false;
	}
	else{
		if(!PE3_Debounced) return false;
		PE3_Debounced = false;
		return true;
	}
}
