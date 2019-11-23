
#ifndef _ADCSWTriggerH_
#define _ADCSWTriggerH_

#include <stdint.h>
#include "ST7735.h"

extern uint32_t joystickData[2];

void ADC_Init89(void);

void ADC_In89(uint32_t data[2]);

#endif