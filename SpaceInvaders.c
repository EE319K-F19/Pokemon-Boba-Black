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
#include "Images.h"
#include "Sound.h"
#include "Timer0.h"
#include "Timer1.h"

#include "Battle.h"
#include "Field.h"
#include "Player.h"
#include "SpaceInvaders.h"
#include "SystemInfo.h"

const SpriteType Bulbasaur = {bulbasaur, 40, 40};
const SpriteType Charmander = {charmander, 40, 40};
const SpriteType Squirtle = {squirtle, 40, 40};
const SpriteType PlayerSprite = {player, 16, 16};
PlayerType p1 = {0, 0, &PlayerSprite};

SpriteInstanceType *sprites;
uint32_t x = 0;
uint32_t y = 0;

SpriteSelectType starter;
FieldType mainField = {fieldArray, 64, 40, 0, 0};

int main(void){
  DisableInterrupts();
  PLL_Init(Bus80MHz);       // Bus clock is 80 MHz 
  Random_Init(1);

  Output_Init();
  ST7735_FillScreen(0x0000);            // set screen to white
  
	//ST7735_SetCursor(1, 1);
  //ST7735_OutString("Pokemon");
	//ST7735_SetCursor(1, 2);
  //ST7735_OutString("Andy & Iris");
	
	//ST7735_SetCursor(1, 3);
  //ST7735_OutString("Welcome, newbie.");
	//ST7735_SetCursor(1, 4);
  //ST7735_OutString("Please select your Pokemon");
	
  //ST7735_DrawBitmap(52, 159, ns, 18,8); // player ship middle bottom
  //ST7735_DrawBitmap(53, 151, Bunker0, 18,5);

  //ST7735_DrawBitmap(0, 9, SmallEnemy10pointA, 16,10);
  //ST7735_DrawBitmap(20,9, SmallEnemy10pointB, 16,10);
  //ST7735_DrawBitmap(40, 9, SmallEnemy20pointA, 16,10);
  //ST7735_DrawBitmap(60, 9, SmallEnemy20pointB, 16,10);
  //ST7735_DrawBitmap(80, 9, SmallEnemy30pointA, 16,10);
  //ST7735_DrawBitmap(100, 9, SmallEnemy30pointB, 16,10);	
	
  //Delay100ms(50);              // delay 5 sec at 80 MHz

  //ST7735_FillScreen(0x0000);            // set screen to black
  //ST7735_SetCursor(1, 1);
  //ST7735_OutString("GAME OVER");
  //ST7735_SetCursor(1, 2);
  //ST7735_OutString("Nice try,");
  //ST7735_SetCursor(1, 3);
  //ST7735_OutString("Earthling!");
  //ST7735_SetCursor(2, 4);
  //LCD_OutDec(1234);
  
	//uint32_t topleft = 0xBFAF;
	//uint32_t botright = 0xB15F;
	
	//for(int i=0; i<30000; i++){
		//int column = i%150;
		//int row = i/200;
		//BackgroundStuff[i] = topleft + 
			//((botright&0x0100)-(topleft&0x0100))*column/80 +
		  //((botright&0x0010)-(topleft&0x0010))*row/80;
	//}
	
	
	SpriteInstanceType poke1 = {2, 130, Bulbasaur};
  SpriteInstanceType poke2 = {42, 130, Charmander};
  SpriteInstanceType poke3 = {84, 130, Squirtle};
  SpriteInstanceType starters[3] = {poke1, poke2, poke3};
	starter = (SpriteSelectType) {starters, 3, 1};
	//DrawSpriteImg(poke1);
	
	//ST7735_DrawBitmap(0, 0xA0, BackgroundStuff, 0x80, 0xA0);
	
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
		
		DrawField(mainField);
		DrawSpriteImgPlayer(p1);
		//p1.XPos++;
		//DrawSpriteImg()
		//mainField.XPos ++;
		p1.XPos++;
		Delay100ms(5);
  }

}
