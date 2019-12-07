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

#include <stdlib.h>
#include <string.h>
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
#include "PokemonType.h"
#include "ImagesPokemon2.h"
#include "Draw.h"
#include "ImagesOther.h"
#include "SpaceInvaders.h"

#include "Shop.h"
#include "SystemInfo.h"
#include "Player.h"
#include "Battle.h"
#include "TextSprites.h"
#include "Battle.h"
#include "DrawScreen.h"
#include "PokemonType.h"
#include "Pokemon.h"

uint8_t ADCStatus;
uint8_t language; // 0 for English, 1 for Spanish

int main(void){
	DisableInterrupts();
  PLL_Init(Bus80MHz);       // Bus clock is 80 MHz 
  Random_Init(1);
  Output_Init();
  
	//interrupt initializations
	Sound_Init();
	ADC_Init89();
	ST7735_InitR(INITR_REDTAB);
	SysTick_Init();
	
  EnableInterrupts();
	
	InitGridCoordinates();
	ClearScreenGrid();
	InitBackgroundTypes();
	InitShop();
	InitPlayer();
	InitInventory();
	InitPokemon();
	InitMoves();
	language = DrawLanguageSelection();
	PokemonType starterT = DrawTitleScreen(language);
	PokemonInstType starterPokemon = {0, 0, starterT.mhealth, starterT, false, 0, starterT.menergy};
	InitTeam();
	addPokemon(&starterPokemon, pokeTeam.size);
	//StartTeam();
	bool win = DrawWorld(language);
	PrintWinLoseScreen(win, language);
}

void PrintWinLoseScreen(bool win, uint8_t language){
	ST7735_FillScreen(0xFFFF);
	
	SpriteType pokemonTitleS; 
	if(language) pokemonTitleS = (SpriteType) {pokemonnameSpanish, 128, 54};
	else pokemonTitleS = (SpriteType) {pokemonname, 128, 54};
	SpriteInstType pokemonTitle = {0, pokemonTitleS.height+10, pokemonTitleS};
	DrawSpriteImg(pokemonTitle);
	
	ST7735_SetTextColor(ST7735_BLACK);
	ST7735_SetCursor(1, 8);
	if(win) {
		if(language) ST7735_OutString("Tu personaje\n es muy feliz!\n Tu ganas!");
		else ST7735_OutString("Your character\n is very full\n on boba!\n You win!");
	}
	else{
		if(language) ST7735_OutString("Tu personaje\n esta muy\n triste.\n Tu pierdes!");
		else ST7735_OutString("Your character is\n  sad.\n  He dropped out of \n  his major.");
	}
}
