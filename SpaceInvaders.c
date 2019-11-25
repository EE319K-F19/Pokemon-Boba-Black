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
#include "Battle.h"
#include "DrawScreen.h"
#include "Field.h"
#include "Shop.h"
#include "SystemInfo.h"
#include "Player.h"

#include "SpaceInvaders.h"
#include "ImagesOther.h"

uint8_t ADCStatus;

static PlayerType p1;
static FieldType mainField = {fieldArray, 64, 40};

int main(void){
  PLL_Init(Bus80MHz);       // Bus clock is 80 MHz 
  Random_Init(1);
  Output_Init();
  
	ADC_Init89();
	ST7735_InitR(INITR_REDTAB);
	SysTick_Init();
  EnableInterrupts();
	
	InitFieldArray();
	InitPokemon();
	InitPlayer();
	
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
	
	const PokemonInstType pokemons[3] = {CharmanderStart, SquirtleStart, BulbasaurStart};
	
	SpriteSelectType starterScreen = {starterInsts, 3, 0};
	//DrawWorld(p1, mainField);
	while(1){
	//ST7735_SetCursor(5, 1);
	ST7735_FillScreen(0xFFFF);
	uint32_t rannum = Random()%3;
	
	//char num = rannum + 0x30;
	//ST7735_OutString(&num);
	PokemonInstType selected = pokemons[rannum];
	DrawBattleScreen(&BulbasaurStart, &selected);
	Delay100ms(15);
	}
	
	//DrawTitleScreen(starterScreen);
	
	//DrawWorld();
	
	//battle screen
	//ST7735_FillScreen(0xFFFF);
	
	//PokemonInstType pokeleft = {2, 100, Bulbasaur, 100, 100, 10, 10, 10, 10, 10};
	//PokemonInstType pokeright = {2, 100, Bulbasaur, 100, 100, 10, 10, 10, 10, 10};
	
}

void InitPlayer(){
	SpriteType PlayerFront = {playerFront, 16, 16};
	SpriteType PlayerBack = {playerBack, 16, 16};
	SpriteType PlayerSide = {playerSide, 16, 16};
	p1 = (PlayerType) {SCREEN_MID_COL+5, SCREEN_MID_ROW+5, &PlayerFront, &PlayerFront, &PlayerBack, &PlayerSide, &PlayerSide, 0, 25};
}
