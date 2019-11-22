// put implementations for functions, explain how it works
// put your names here, date

#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"

// ADC initialization function 
// Input: none
// Output: none
// measures from PD2, analog channel 5
void ADC_Init(void){
	SYSCTL_RCGCGPIO_R |= 0x08;
	volatile int delay = 0;
	delay++;

	GPIO_PORTD_DIR_R &= ~0x04;
	GPIO_PORTD_DEN_R &= ~0x04;
	GPIO_PORTD_AFSEL_R |= 0x04; // turn on alternate function
	GPIO_PORTD_AMSEL_R |= 0x04; // turn on analog

	SYSCTL_RCGCADC_R |= 0x01; // activate ADC0
	delay++;
	delay++;

	ADC0_PC_R |= 0x01; // set smapling rate to 125kHz
	ADC0_SSPRI_R = 0x0123; // set sequencer 3 as highest priority
	ADC0_ACTSS_R &= 0x08; // disable sample sequencer 3
	ADC0_EMUX_R &= ~0xF000; // sequence 3 is S/W trigger
	ADC0_SSMUX3_R = (ADC0_SSMUX3_R & 0xFFFFFFF0) + 5;
	ADC0_SSCTL3_R = 0x0006;
	ADC0_IM_R &= ~0x0008; // disable SS3 interrupts
	ADC0_ACTSS_R |= 0x08; // enable SS3
	//ADC0_SAC_R = 0x06; // average sample to get better distances values
}


//------------ADC_In------------
// Busy-wait Analog to digital conversion
// Input: none
// Output: 12-bit result of ADC conversion
// measures from PD2, analog channel 5
uint32_t ADC_In(void){  
	uint32_t data;
  ADC0_PSSI_R = 0x0008;	//start adc
  while((ADC0_RIS_R&0x08)==0){};   //wait for flag
  data = ADC0_SSFIFO3_R&0xFFF;  //read data
  ADC0_ISC_R = 0x0008;  //clear flag
  return data;
}



