// SpaceInvaders.c
// Runs on LM4F120/TM4C123
// Jonathan Valvano and Daniel Valvano
// This is a starter project for the EE319K Lab 10

// Last Modified: 9/2/2019 
// http://www.spaceinvaders.de/
// sounds at http://www.classicgaming.cc/classics/spaceinvaders/sounds.php
// http://www.classicgaming.cc/classics/spaceinvaders/playguide.php
/* This example accompanies the books
   "Embedded Systems: Real Time Interfacing to Arm Cortex M Microcontrollers",
   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2019

   "Embedded Systems: Introduction to Arm Cortex M Microcontrollers",
   ISBN: 978-1469998749, Jonathan Valvano, copyright (c) 2019

 Copyright 2019 by Jonathan W. Valvano, valvano@mail.utexas.edu
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
// ******* Possible Hardware I/O connections*******************
// Slide pot pin 1 connected to ground
// Slide pot pin 2 connected to PD2/AIN5
// Slide pot pin 3 connected to +3.3V 
// fire button connected to PE0
// special weapon fire button connected to PE1
// 8*R resistor DAC bit 0 on PB0 (least significant bit)
// 4*R resistor DAC bit 1 on PB1
// 2*R resistor DAC bit 2 on PB2
// 1*R resistor DAC bit 3 on PB3 (most significant bit)
// LED on PB4
// LED on PB5

// Backlight (pin 10) connected to +3.3 V
// MISO (pin 9) unconnected
// SCK (pin 8) connected to PA2 (SSI0Clk)
// MOSI (pin 7) connected to PA5 (SSI0Tx)
// TFT_CS (pin 6) connected to PA3 (SSI0Fss)
// CARD_CS (pin 5) unconnected
// Data/Command (pin 4) connected to PA6 (GPIO), high for data, low for command
// RESET (pin 3) connected to PA7 (GPIO)
// VCC (pin 2) connected to +3.3 V
// Gnd (pin 1) connected to ground

#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
#include "ST7735.h"
#include "Random.h"
#include "PLL.h"
#include "ADC.h"
#include "ImagesPokemon.h"
#include "ImagesOther.h"
#include "Sound.h"
#include "Timer0.h"
#include "Timer1.h"

#include "Battle.h"
#include "Field.h"
#include "SystemInfo.h"

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts

const SpriteType Bulbasaur = {bulbasaur, 40, 40};
const SpriteType Charmander = {charmander, 40, 40};
const SpriteType Squirtle = {squirtle, 40, 40};

const SpriteType PlayerFront = {playerFront, 16, 16};
const SpriteType PlayerBack = {playerBack, 16, 16};
const SpriteType PlayerSide = {playerSide, 16, 16};

PlayerType p1;

SpriteSelectType starter;
FieldType mainField = {fieldArray, 64, 40, 0, 0};

int main(void){
  DisableInterrupts();
  PLL_Init(Bus80MHz);       // Bus clock is 80 MHz 
  Random_Init(1);
  Output_Init();
  
	ST7735_FillScreen(0xFFFF);
	DrawBorder(GAME_BORDER_W, GAME_BORDER_W, _width-2*GAME_BORDER_W, _height-2*GAME_BORDER_W, GAME_BORDER_W, GAME_BORDER_COLOR);
	
	SpriteInstanceType poke1 = {2, 130, Bulbasaur};
  SpriteInstanceType poke2 = {42, 130, Charmander};
  SpriteInstanceType poke3 = {84, 130, Squirtle};
  SpriteInstanceType starters[3] = {poke1, poke2, poke3};
	starter = (SpriteSelectType) {starters, 3, 1};
	
	p1 = (PlayerType) {SCREEN_MID_COL, SCREEN_MID_ROW, &PlayerFront};
	//DrawSpriteImg(poke1);
	
	//ST7735_DrawBitmap(0, 0xA0, BackgroundStuff, 0x80, 0xA0);
	DrawField(p1, mainField);
	while(1){
		//ST7735_FillScreen(0xFFFF);   
		//ST7735_FillRect(128-x, 0, x, 160-y, 0xF50F);
		//ST7735_FillRect(0, 160-y, 128-x, y, 0x6FFF);
		//ST7735_FillRect(128-x, 160-y, 128-x, 160-y, 0x00FF);
		//ST7735_SetCursor(1, 1);
		//ST7735_OutString("Pokemon Boba Black");
		//ST7735_SetCursor(1, 2);
		//ST7735_OutString("Andy & Iris");
	
		//ST7735_SetCursor(1, 3);
		//ST7735_OutString("Welcome, newbie.");
		//ST7735_SetCursor(1, 4);
		//ST7735_OutString("Please select your Pokemon");
		//DrawStartScreen(&starter);
		//x+=3;
		//y+=2;
		
		
		//DrawSpriteImgPlayer(p1);
		//p1.XPos++;
		//DrawSpriteImg()
		//mainField.XPos ++;
		//p1.XPos++;
		//Delay100ms(5);
  }

}
