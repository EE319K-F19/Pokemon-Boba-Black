#ifndef _ADCJoystick_
#define _ADCJoystick_

#include <stdint.h>
#include "ST7735.h"

extern uint32_t joystickData[2];
extern uint8_t ADCStatus;

void ADC_Init89(void);

void ADC_In89(uint32_t data[2]);

void SysTick_Init(void);

void SysTick_Handler(void);

uint32_t getJoystickX(void);
uint32_t getJoystickY(void);

int Joystick_main(void);

#endif