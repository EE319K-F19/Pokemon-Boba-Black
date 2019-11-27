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
#include "PLL.h"
#include "ADC.h"
#include "Sound.h"
#include "Timer0.h"
#include "Timer1.h"
#include "Random.h"

#include "ADC_Joystick.h"
#include "Battle.h"
#include "Field.h"
#include "ImagesOther.h"
#include "PokemonType.h"
#include "ImagesPokemon2.h"
#include "DrawScreen.h"
#include "SpaceInvaders.h"

#include "Shop.h"
#include "SystemInfo.h"
#include "Player.h"

uint8_t ADCStatus;

static PlayerType p1;
static FieldType mainField = {fieldArray, 64, 40};

PokemonType starters[3];
SpriteInstType starterInsts[3];

ItemInstType shopItems[3];
SpriteInstType itemInsts[3];

int main1(void){
	PLL_Init(Bus80MHz);
	Sound_Init();
	ADC_Init89();
	Shop_Init();
	EnableInterrupts();
	while(1){
		//Sound_Highpitch();
		//ST7735_SetCursor(0,0);
		//ST7735_OutString("SW: ");
		//LCD_OutDec(portEDataPE3);
		//ST7735_OutString("\n");
		
	}
}

int main(void){
  PLL_Init(Bus80MHz);       // Bus clock is 80 MHz 
  Random_Init(1);
  Output_Init();
  
	ADC_Init89();
	ST7735_InitR(INITR_REDTAB);
	SysTick_Init();
  EnableInterrupts();
	Shop_Init();
	ClearScreenGrid();
	InitBackgroundTypes();
	InitFieldArray();
	InitPokemon();
	
	//while(1){
		//SpriteSelectType shopScreen = {itemInsts, 3, 0};
		
		//DrawShopScreen(shopScreen, shopItems);
	//}
	SpriteSelectType starterScreen = {starterInsts, 3, 0};
	PokemonType starter = DrawTitleScreen(starterScreen);
	PokemonTeamType pokemonTeam = {{0, 0, starter.mhealth, starter}, {0, 0, 0, NullT}, {0, 0, 0, NullT}, {0, 0, 0, NullT}, {0, 0, 0, NullT}, {0, 0, 0, NullT}};
	InitPlayer(starter);
	DrawWorld(p1, mainField);
}

void InitPlayer(PokemonType starter){
	SpriteType PlayerFront = {playerFront, 16, 16};
	SpriteType PlayerBack = {playerBack, 16, 16};
	SpriteType PlayerSide = {playerSide, 16, 16};
	SpriteType PlayerSideFlipped = {playerSideFlipped, 16, 16};;
	p1 = (PlayerType) {SCREEN_MID_COL+5, SCREEN_MID_ROW+5, PlayerFront, PlayerFront, PlayerBack, PlayerSide, PlayerSideFlipped, 0, 25};
}
