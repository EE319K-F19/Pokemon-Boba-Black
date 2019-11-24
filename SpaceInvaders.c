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
#include "Sound.h"
#include "Timer0.h"
#include "Timer1.h"

#include "ADC_Joystick.h"
#include "DrawScreen.h"
#include "Battle.h"
#include "Field.h"
#include "ImagesOther.h"
#include "SystemInfo.h"
#include "ImagesPokemon.h"
#include "Draw.h"
#include "SpaceInvaders.h"

uint8_t ADCStatus = 0;

static PlayerType p1;
static FieldType mainField = {fieldArray, 64, 40};

static PokemonType BulbasaurT;
static PokemonType SquirtleT;
static PokemonType CharmanderT;

uint16_t* reverseImage;

int main(void){
  PLL_Init(Bus80MHz);       // Bus clock is 80 MHz 
  Random_Init(1);
  Output_Init();
  
	//ADC_Init89();
	//ST7735_InitR(INITR_REDTAB);
	//SysTick_Init();
  EnableInterrupts();
	
	//SpriteType Bulbasaur = {bulbasaur, 40, 40, 0};
	//SpriteType Charmander = {charmander, 40, 40, 0};
	//SpriteType Squirtle = {squirtle, 40, 40, 0};
	
	SpriteType PlayerFront = {playerFront, 16, 16};
	SpriteType PlayerBack = {playerBack, 16, 16};
	SpriteType PlayerSide = {playerSide, 16, 16};
	p1 = (PlayerType) {SCREEN_MID_COL, SCREEN_MID_ROW, &PlayerFront, &PlayerFront, &PlayerBack, &PlayerSide, &PlayerSide, 0};
	
	SpriteType bulbasaurS = {bulbasaur, 40, 40};
	SpriteType squirtleS = {squirtle, 40, 40};
	SpriteType charmanderS = {charmander, 40, 40};
	
	BulbasaurT = (PokemonType) {"Bulbasaur", Grass, bulbasaurS, 45, 49, 49, 65, 65, 45};
	SquirtleT = (PokemonType) {"Squirtle", Water, squirtleS, 44, 48, 65, 50, 64, 43};
	CharmanderT = (PokemonType) {"Charmander", Fire, charmanderS, 39, 52, 43, 60, 50, 65};
	//SpriteInstanceType poke1 = {2, 130, Bulbasaur};
  //SpriteInstanceType poke2 = {44, 130, Charmander};
  //SpriteInstanceType poke3 = {86, 130, Squirtle};
  //SpriteInstanceType starters[3] = {poke1, poke2, poke3};
	//starterScreen = (SpriteSelectType) {starters, 3, 1};
	
	//PokemonInstType BulbasaurStart = {2, 130, BulbasaurT.mhealth, BulbasaurT};
	//PokemonInstType SquirtleStart = {44, 130, SquirtleT.mhealth, SquirtleT};
	PokemonInstType CharmanderStart = {86, 130, CharmanderT.mhealth, CharmanderT};
	
	PokemonInstType BulbasaurStart = {2, 90, BulbasaurT.mhealth, BulbasaurT};
	PokemonInstType SquirtleStart = {86, 90, SquirtleT.mhealth, SquirtleT};
	           
	const SpriteInstType starterInsts[3] = {
		(SpriteInstType) {BulbasaurStart.xPos, BulbasaurStart.yPos, BulbasaurStart.species.sprite},
		(SpriteInstType) {SquirtleStart.xPos, SquirtleStart.yPos, SquirtleStart.species.sprite},
		(SpriteInstType) {CharmanderStart.xPos, CharmanderStart.yPos, CharmanderStart.species.sprite}
	};
	
	SpriteSelectType starterScreen = {starterInsts, 3, 0};
	DrawBattleScreen(&BulbasaurStart, &SquirtleStart);
	//DrawTitleScreen(starterScreen);
	
	//DrawWorld();
	
	//battle screen
	//ST7735_FillScreen(0xFFFF);
	
	//PokemonInstType pokeleft = {2, 100, Bulbasaur, 100, 100, 10, 10, 10, 10, 10};
	//PokemonInstType pokeright = {2, 100, Bulbasaur, 100, 100, 10, 10, 10, 10, 10};
	
}


void DrawBattleScreen(PokemonInstType* pokeLeft, PokemonInstType* pokeRight){
	ST7735_FillScreen(0xFFFF);
	SpriteInstType leftInst = (SpriteInstType) {pokeLeft->xPos, pokeLeft->yPos, pokeLeft->species.sprite};
	SpriteInstType rightInst = (SpriteInstType) {pokeRight->xPos, pokeRight->yPos, pokeRight->species.sprite};
	
	DrawSpriteImg(leftInst);
	DrawSpriteImg(rightInst);
	
	ST7735_FillRect(pokeLeft->xPos, 30, 40, 2, 0x0000);
	ST7735_FillRect(pokeRight->xPos, 30, 40, 2, 0x0000);
	
	ST7735_FillRect(pokeLeft->xPos, 30, pokeLeft->chealth*40/pokeLeft->species.mhealth, 2, 0x00FF);
	ST7735_FillRect(pokeRight->xPos, 30, pokeRight->chealth*40/pokeRight->species.mhealth, 2, 0x00FF);
	//ST7735_DrawString(pokeLeft->xPos, 30, (pokeLeft->chealth+0x30)+"/"+pokeLeft->species.mhealth, 0x0000)
	
	Delay100ms(15);
	pokeRight->chealth-=12;
	ST7735_FillRect(pokeLeft->xPos, 30, 40, 2, 0x0000);
	ST7735_FillRect(pokeRight->xPos, 30, 40, 2, 0x0000);
	ST7735_FillRect(pokeLeft->xPos, 30, pokeLeft->chealth*40/pokeLeft->species.mhealth, 2, 0x00FF);
	ST7735_FillRect(pokeRight->xPos, 30, pokeRight->chealth*40/pokeRight->species.mhealth, 2, 0x00FF);
	
	
	Delay100ms(15);
	pokeLeft->chealth-=21;
	ST7735_FillRect(pokeLeft->xPos, 30, 40, 2, 0x0000);
	ST7735_FillRect(pokeRight->xPos, 30, 40, 2, 0x0000);
	ST7735_FillRect(pokeLeft->xPos, 30, pokeLeft->chealth*40/pokeLeft->species.mhealth, 2, 0x00FF);
	ST7735_FillRect(pokeRight->xPos, 30, pokeRight->chealth*40/pokeRight->species.mhealth, 2, 0x00FF);
	
	Delay100ms(15);
	pokeRight->chealth-=15;
	ST7735_FillRect(pokeLeft->xPos, 30, 40, 2, 0x0000);
	ST7735_FillRect(pokeRight->xPos, 30, 40, 2, 0x0000);
	ST7735_FillRect(pokeLeft->xPos, 30, pokeLeft->chealth*40/pokeLeft->species.mhealth, 2, 0x00FF);
	ST7735_FillRect(pokeRight->xPos, 30, pokeRight->chealth*40/pokeRight->species.mhealth, 2, 0x00FF);
}

uint16_t* GetReverseXImage(const uint16_t *image, uint8_t w, uint8_t h){
	uint16_t newimage[w*h];
	
	uint16_t length = w*h;
	for(uint8_t i=0; i<h; i++){
			for(uint8_t j=0; j<w; j++){
				uint16_t front = i*w + j;
				uint16_t back = (i+1)*w - j;
				uint16_t temp = image[back];
				newimage[back] = image[front];
				newimage[front] = image[back];
			}
	}
	reverseImage = newimage;
	return reverseImage;
}

void DrawTitleScreen(SpriteSelectType starterScreen){
	ST7735_FillScreen(0xFFFF);
	
	DrawAllSprites(starterScreen);
	ST7735_SetTextColor(ST7735_BLACK);
	ST7735_SetCursor(1, 1);
	ST7735_OutString("Pokemon Boba Black");
	ST7735_SetCursor(1, 2);
	ST7735_OutString("Made by Andy & Iris");
	ST7735_SetCursor(1, 3);
	ST7735_OutString("Please select your\n starter.");
	while(1){
		
		while(ADCStatus == 0){}
			
		uint8_t xDir = getJoystickX();
		uint8_t yDir = getJoystickY();
		ADCStatus = 0;
		
		if(xDir == 2){
			starterScreen.currentIndex = (starterScreen.currentIndex + 1)%3;
		}else if(xDir == 0){
			starterScreen.currentIndex = starterScreen.currentIndex - 1;
			if(starterScreen.currentIndex < 0) starterScreen.currentIndex = 2;
		}
			
		DrawSelection(&starterScreen, 0x0000, 0xFFFF, 1);
		Delay100ms(2);
  }
}

void DrawWorld(){
	//draws black border around the edges of the screen
	DrawBorder(GAME_BORDER_W, GAME_BORDER_W, _width-2*GAME_BORDER_W, _height-2*GAME_BORDER_W, GAME_BORDER_W, GAME_BORDER_COLOR);

	while(1){
	while(ADCStatus == 0){}
			
	uint8_t xDir = getJoystickX();
	uint8_t yDir = getJoystickY();
	ADCStatus = 0;
		
	if(xDir == 0){
		MoveLeft(&p1);
	}else if(xDir == 2){
		MoveRight(&p1);
	}else if(yDir == 0){
		MoveUp(&p1);
	}else if(yDir == 2){
		MoveDown(&p1);
	}
		
	DrawField(p1, mainField);
	}
}



