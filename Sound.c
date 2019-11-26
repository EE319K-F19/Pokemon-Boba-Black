// Sound.c
// Runs on any computer
// Sound assets based off the original Space Invaders 
// Import these constants into your SpaceInvaders.c for sounds!
// Jonathan Valvano
// November 17, 2014
#include <stdint.h>
#include "Sound.h"
#include "DAC.h"
#include "Timer0.h"
#include "../inc/tm4c123gh6pm.h"

const uint8_t highpitch[1802] = {		
  63, 41, 26, 25, 12, 2, 12, 15, 28, 38, 40, 44, 41, 57, 55, 50, 39, 30, 19, 24, 		
  8, 3, 12, 16, 29, 39, 41, 43, 45, 62, 52, 49, 36, 26, 21, 18, 2, 8, 13, 23, 		
  35, 39, 44, 41, 56, 57, 50, 42, 31, 20, 24, 5, 5, 12, 18, 30, 39, 43, 40, 52, 		
  60, 51, 46, 34, 21, 25, 6, 2, 11, 16, 29, 39, 42, 41, 52, 60, 51, 46, 34, 22, 		
  24, 6, 3, 11, 18, 29, 38, 42, 41, 56, 58, 51, 43, 31, 22, 20, 2, 6, 12, 23, 		
  31, 41, 41, 46, 62, 53, 50, 37, 23, 24, 9, 2, 11, 16, 28, 38, 42, 42, 57, 57, 		
  51, 40, 28, 24, 15, 0, 9, 13, 26, 35, 42, 41, 55, 59, 51, 43, 29, 25, 14, 0, 		
  9, 13, 26, 35, 42, 41, 55, 59, 51, 43, 28, 25, 14, 0, 9, 14, 27, 37, 39, 44, 		
  60, 56, 51, 39, 27, 25, 6, 2, 11, 19, 29, 40, 38, 52, 62, 52, 46, 32, 27, 15, 		
  0, 8, 13, 26, 36, 39, 45, 61, 56, 50, 38, 27, 22, 3, 3, 11, 23, 31, 40, 40, 		
  59, 58, 51, 41, 30, 23, 5, 2, 11, 20, 31, 41, 39, 58, 59, 52, 42, 29, 23, 5, 		
  2, 11, 22, 32, 39, 43, 61, 57, 51, 37, 30, 18, 1, 5, 12, 26, 36, 37, 50, 63, 		
  53, 49, 32, 29, 10, 0, 9, 15, 27, 37, 37, 58, 61, 52, 38, 31, 17, 1, 6, 12, 		
  23, 35, 36, 54, 63, 53, 44, 31, 23, 4, 2, 11, 23, 33, 36, 51, 63, 54, 47, 33, 		
  26, 5, 1, 10, 22, 32, 36, 52, 63, 54, 46, 34, 21, 5, 2, 11, 24, 35, 36, 55, 		
  62, 53, 41, 36, 15, 1, 5, 14, 27, 35, 42, 61, 58, 52, 36, 32, 8, 0, 10, 19, 		
  32, 35, 53, 63, 53, 44, 36, 15, 1, 5, 15, 27, 34, 46, 63, 57, 49, 36, 25, 4, 		
  2, 11, 25, 34, 41, 59, 60, 51, 38, 29, 5, 1, 10, 23, 32, 40, 59, 60, 51, 38, 		
  28, 5, 1, 10, 24, 31, 43, 59, 60, 49, 38, 23, 2, 2, 13, 26, 32, 48, 63, 56, 		
  44, 39, 13, 0, 8, 16, 29, 35, 54, 63, 52, 41, 31, 6, 0, 12, 23, 28, 46, 63, 		
  58, 46, 38, 12, 0, 10, 16, 29, 39, 57, 62, 48, 41, 22, 2, 3, 13, 27, 33, 54, 		
  63, 51, 42, 27, 4, 1, 13, 26, 32, 53, 63, 50, 43, 28, 4, 1, 14, 27, 31, 54, 		
  63, 49, 43, 24, 3, 5, 14, 27, 36, 57, 62, 46, 42, 16, 0, 12, 18, 27, 46, 62, 		
  56, 46, 34, 7, 0, 12, 25, 31, 55, 63, 48, 43, 18, 0, 12, 17, 26, 47, 63, 53, 		
  46, 29, 5, 2, 16, 25, 39, 59, 60, 47, 35, 9, 0, 14, 25, 32, 58, 62, 46, 40, 		
  10, 0, 14, 23, 33, 57, 62, 47, 39, 8, 0, 15, 23, 35, 58, 62, 45, 37, 9, 0, 		
  17, 23, 40, 60, 56, 49, 29, 6, 3, 18, 24, 48, 63, 49, 48, 17, 0, 14, 18, 32, 		
  55, 63, 47, 35, 11, 0, 18, 22, 47, 63, 49, 48, 15, 0, 17, 17, 36, 59, 57, 50, 		
  27, 5, 8, 17, 28, 54, 63, 47, 34, 8, 0, 19, 25, 51, 63, 46, 40, 10, 0, 19, 		
  22, 51, 63, 47, 40, 10, 0, 21, 23, 52, 63, 47, 37, 9, 2, 18, 26, 54, 63, 49, 		
  28, 5, 10, 17, 34, 58, 57, 50, 17, 0, 18, 17, 45, 63, 49, 43, 11, 0, 15, 26, 		
  53, 60, 48, 22, 2, 15, 15, 44, 62, 48, 41, 8, 3, 17, 32, 56, 57, 47, 14, 0, 		
  18, 24, 52, 62, 49, 20, 1, 16, 18, 51, 63, 50, 25, 3, 15, 16, 48, 62, 50, 26, 		
  5, 15, 17, 49, 62, 50, 24, 4, 16, 19, 51, 63, 47, 20, 2, 16, 27, 52, 63, 44, 		
  15, 1, 17, 36, 55, 58, 36, 11, 8, 17, 47, 61, 49, 22, 3, 16, 27, 52, 62, 38, 		
  15, 4, 17, 45, 61, 50, 21, 3, 16, 31, 54, 60, 33, 11, 11, 19, 49, 62, 42, 16, 		
  3, 17, 45, 61, 47, 19, 3, 16, 41, 58, 52, 21, 5, 16, 37, 56, 54, 22, 4, 16, 		
  36, 56, 53, 22, 6, 16, 38, 58, 51, 20, 5, 17, 42, 59, 44, 17, 6, 19, 48, 62, 		
  37, 14, 9, 23, 52, 58, 26, 8, 15, 36, 57, 48, 19, 6, 21, 46, 63, 29, 10, 15, 		
  33, 55, 46, 20, 7, 23, 48, 60, 25, 8, 18, 39, 61, 34, 15, 11, 31, 56, 45, 21, 		
  6, 26, 48, 56, 23, 6, 24, 44, 62, 24, 7, 23, 41, 62, 24, 10, 20, 39, 63, 26, 		
  10, 22, 39, 61, 24, 9, 24, 41, 61, 22, 6, 29, 44, 55, 22, 5, 34, 52, 41, 22, 		
  10, 37, 59, 27, 15, 22, 40, 58, 22, 6, 34, 50, 39, 22, 13, 40, 58, 23, 8, 32, 		
  50, 40, 20, 14, 41, 58, 22, 6, 36, 52, 32, 16, 25, 44, 46, 20, 13, 42, 55, 20, 		
  8, 40, 54, 25, 10, 36, 50, 30, 14, 31, 49, 35, 15, 28, 46, 37, 16, 26, 48, 37, 		
  17, 27, 45, 36, 16, 28, 49, 33, 14, 33, 50, 26, 12, 40, 50, 23, 11, 45, 49, 19, 		
  17, 47, 41, 15, 30, 48, 26, 13, 43, 50, 19, 17, 49, 38, 13, 38, 47, 21, 13, 48, 		
  41, 13, 38, 46, 21, 15, 50, 35, 12, 44, 44, 17, 26, 50, 25, 13, 51, 37, 11, 47, 		
  41, 15, 35, 45, 20, 23, 50, 25, 15, 53, 29, 13, 53, 32, 12, 52, 35, 12, 47, 40, 		
  14, 38, 45, 20, 23, 50, 26, 13, 50, 35, 12, 38, 45, 17, 19, 50, 31, 9, 46, 44, 		
  16, 23, 48, 30, 12, 44, 47, 17, 19, 49, 37, 13, 34, 48, 25, 12, 43, 50, 19, 13, 		
  46, 47, 18, 20, 47, 41, 15, 26, 48, 36, 16, 29, 48, 35, 15, 27, 47, 37, 17, 25, 		
  47, 41, 18, 19, 45, 48, 20, 11, 44, 55, 20, 8, 39, 54, 27, 13, 31, 47, 42, 20, 		
  13, 43, 57, 18, 8, 38, 52, 34, 18, 18, 43, 58, 18, 7, 35, 50, 43, 19, 11, 40, 		
  58, 26, 16, 21, 41, 62, 19, 8, 29, 45, 56, 18, 5, 33, 49, 49, 21, 5, 35, 52, 		
  46, 20, 6, 34, 52, 47, 20, 5, 32, 50, 51, 19, 5, 27, 49, 59, 19, 8, 23, 44, 		
  63, 25, 12, 15, 38, 60, 37, 17, 9, 28, 53, 54, 20, 6, 20, 45, 61, 35, 13, 11, 		
  28, 52, 56, 21, 7, 18, 42, 62, 42, 14, 6, 21, 52, 62, 31, 12, 12, 26, 53, 58, 		
  23, 8, 17, 31, 55, 54, 20, 7, 18, 35, 56, 53, 20, 6, 18, 35, 57, 55, 22, 8, 		
  16, 30, 55, 58, 26, 10, 11, 25, 54, 62, 34, 13, 6, 19, 50, 62, 44, 14, 2, 18, 		
  40, 57, 54, 24, 8, 15, 22, 54, 61, 40, 13, 2, 19, 42, 57, 54, 27, 8, 11, 20, 		
  52, 62, 45, 15, 3, 18, 28, 57, 60, 40, 11, 2, 19, 36, 56, 57, 38, 8, 4, 17, 		
  40, 58, 55, 37, 8, 5, 19, 38, 59, 54, 40, 7, 3, 19, 35, 57, 57, 43, 11, 1, 		
  20, 26, 58, 61, 46, 17, 2, 17, 19, 51, 61, 49, 35, 5, 7, 18, 36, 59, 57, 46, 		
  12, 2, 19, 19, 54, 62, 47, 37, 5, 3, 20, 30, 58, 62, 47, 20, 4, 13, 17, 40, 		
  59, 56, 47, 12, 3, 18, 17, 45, 61, 50, 46, 10, 0, 20, 18, 48, 61, 52, 47, 10, 		
  1, 18, 18, 43, 59, 56, 46, 15, 2, 15, 19, 37, 60, 60, 45, 25, 5, 6, 20, 27, 		
  58, 63, 45, 41, 4, 0, 21, 22, 47, 61, 52, 46, 19, 2, 11, 20, 30, 59, 62, 44, 		
  38, 4, 1, 17, 21, 39, 60, 59, 43, 30, 4, 1, 19, 25, 47, 60, 54, 44, 23, 2, 		
  5, 19, 28, 49, 62, 52, 45, 21, 3, 6, 18, 28, 50, 62, 53, 44, 22, 3, 3, 19, 		
  29, 45, 61, 57, 43, 31, 2, 1, 17, 27, 37, 63, 60, 44, 39, 6, 0, 18, 20, 32, 		
  55, 63, 50, 44, 22, 1, 4, 18, 29, 40, 63, 58, 44, 38, 7, 0, 16, 20, 32, 50, 		
  63, 54, 44, 32, 3, 1, 16, 24, 32, 56, 63, 49, 42, 28, 2, 2, 18, 26, 33, 57, 		
  62, 48, 42, 27, 1, 2, 17, 26, 33, 56, 63, 51, 43, 29, 1, 2, 17, 24, 33, 50, 		
  62, 55, 42, 35, 5, 0, 14, 19, 33, 39, 62, 58, 45, 38, 20, 0, 5, 17, 28, 34, 		
  54, 63, 51, 42, 34, 4, 1, 12, 20, 32, 37, 62, 60, 46, 40, 26, 0, 3, 15, 24, 		
  35, 44, 63, 57, 45, 37, 22, 0, 4, 16, 26, 33, 46, 63, 57, 45, 35, 22, 0, 5, 		
  16, 26, 35, 45, 63, 57, 46, 37, 25, 0, 3, 15, 25, 35, 39, 63, 58, 47, 39, 29, 		
  3, 1, 13, 18, 34, 35, 53, 63, 53, 44, 31, 18, 0, 6, 16, 28, 35, 41, 63, 57, 		
  47, 38, 29, 4, 1, 11, 19, 31, 37, 48, 63, 55, 46, 33, 26, 0, 3, 13, 23, 35, 		
  36, 53, 63, 53, 44, 31, 25, 0, 5, 13, 23, 35, 38, 54, 62, 53, 44, 30, 26, 0, 		
  4, 14, 21, 35, 38, 47, 63, 54, 46, 35, 27, 3, 2, 11, 18, 34, 38, 41, 63, 55, 		
  49, 39, 28, 17, 0, 7, 16, 28, 36, 39, 53, 62, 53, 43, 32, 26, 3, 2, 11, 18, 		
  34, 40, 38, 63, 57, 51, 41, 27, 25, 0, 4, 13, 21, 35, 40, 41, 63, 55, 49, 38, 		
  27, 23, 0, 6, 15, 22, 35, 40, 41, 63, 55, 51, 37, 28, 23, 0, 6, 13, 21, 36, 		
  40, 39, 61, 57, 51, 42, 28, 25, 6, 2, 10, 17, 32, 39, 41, 49, 63, 53, 47, 33, 		
  25, 19, 0, 8, 15, 24, 37, 40, 41, 60, 56, 50, 40, 27, 22, 8, 2, 11, 15, 29, 		
  38, 41, 42, 63, 54, 48, 37, 27, 23, 3, 3, 11, 17, 31, 38, 42, 44, 63, 53, 48, 		
  37, 26, 23, 3, 3, 11, 17, 32, 40, 41, 44, 63, 53, 50, 39, 25, 23, 11, 1, 11, 		
  17, 30, 37, 42, 41, 60, 56, 51, 44, 28, 24, 20, 0, 9, 14, 25, 36, 40, 42, 46, 		
  63, 52};

	uint32_t idx = 0;
	uint8_t* sound;
	uint32_t len;

void Sound_Init(void){
// write this
	DAC_Init();
	Timer0_Init(Play_Sound, 7256);
};

void Play_Sound(void){
	DAC_Out(sound[idx]);
	idx = (idx + 1) % len;
};

void Sound_Highpitch(void){
// write this
	sound = (uint8_t*)highpitch;
	len = 1802;
	Play_Sound();
};

void Sound_Play(const uint8_t *pt, uint32_t count){
// write this
};
void Sound_Shoot(void){
// write this
};
void Sound_Killed(void){
// write this
};
void Sound_Explosion(void){
// write this
};

void Sound_Fastinvader1(void){
// write this
};
void Sound_Fastinvader2(void){
// write this
};
void Sound_Fastinvader3(void){
// write this
};
void Sound_Fastinvader4(void){
// write this
};

uint32_t portEDataPE3;
int sound_main(void){
	volatile uint8_t delay;
	//PLL_Init(Bus80MHz);
	Sound_Init();
	SYSCTL_RCGCGPIO_R |= 0x10;
	delay++;
	delay++;
	GPIO_PORTE_DIR_R &= ~0x0C;
	GPIO_PORTE_PDR_R |= 0x0C;
	GPIO_PORTE_DEN_R |= 0x0C;
	//ST7735_InitR(INITR_REDTAB);
	// ADC_Init89();
	//EnableInterrupts();
	while(1){
		portEDataPE3 = GPIO_PORTE_DATA_R & 0x08;;
		// Sound_Highpitch();
		//ST7735_SetCursor(0,0);
		//ST7735_OutString("SW: ");
		//LCD_OutDec(portEDataPE3);
		// ST7735_OutString("\n");
	}
}

int sound_main2(void){
	//PLL_Init(Bus80MHz);
	Sound_Init();
	//ADC_Init89();
	//EnableInterrupts();
	while(1){
		Sound_Highpitch();
		//ST7735_SetCursor(0,0);
		//ST7735_OutString("SW: ");
		//LCD_OutDec(portEDataPE3);
		// ST7735_OutString("\n");
	}
}


