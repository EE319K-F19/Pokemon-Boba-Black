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
#include "ImagesOther.h"
#include "PokemonType.h"
#include "ImagesPokemon2.h"
#include "Draw.h"
#include "SpaceInvaders.h"

#include "Shop.h"
#include "SystemInfo.h"
#include "Player.h"
#include "Battle.h"
#include "TextSprites.h"
#include "Battle.h"
#include "PokemonType.h"

uint8_t ADCStatus;

static PlayerType p1;

PokemonType starters[3];
SpriteInstType starterInsts[3];

ItemInstType shopItems[3];
SpriteInstType itemInsts[3];
PokemonInstType* team;

PokemonType NullT;
PokemonType BulbasaurT;
PokemonType SquirtleT;
PokemonType CharmanderT;
PokemonType PidgeyT;
PokemonType PikachuT;

int main1(void){
	PLL_Init(Bus80MHz);
	Sound_Init();
	ADC_Init89();
	Shop_Init();
	InitMoves();
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
	InitMoves();
	//PokemonInstType poke = {0, 0, BulbasaurT.mhealth, BulbasaurT};
	//PokemonInstType poke2 = {0, 0, BulbasaurT.mhealth, BulbasaurT};
	//DrawMoveCommands(&poke, &poke2);
	//while(1){
		//SpriteSelectType shopScreen = {itemInsts, 3, 0};
		
		//DrawShopScreen(shopScreen, shopItems);
	//}
	SpriteSelectType starterScreen = {starterInsts, 3, 0};
	PokemonType starterT = DrawTitleScreen(starterScreen);

	PokemonInstType startteam[1] = {{0, 0, starterT.mhealth, starterT}};
	team = startteam;
	InitPlayer();
	DrawWorld(p1);
}

void InitPlayer(){
	SpriteType PlayerFront = {playerFront, 16, 16};
	SpriteType PlayerBack = {playerBack, 16, 16};
	SpriteType PlayerSide = {playerSide, 16, 16};
	SpriteType PlayerSideFlipped = {playerSideFlipped, 16, 16};
	p1 = (PlayerType) {SCREEN_MID_COL+5, SCREEN_MID_ROW+5, PlayerFront, PlayerFront, PlayerBack, PlayerSide, PlayerSideFlipped, 0, 25};
}


void InitPokemon(){
	//uint16_t nullSprite[1] = {0x0000};
	//SpriteType nullS = {nullSprite, 1, 1};
	SpriteType bulbasaurS = {bulbasaur, 40, 40};
	SpriteType squirtleS = {squirtle, 40, 40};
	SpriteType charmanderS = {charmander, 40, 40};
	SpriteType pidgeyS = {pidgey, 40, 40};
	SpriteType pikachuS = {pikachu, 40, 40};
	
	//NullT = (PokemonType) {"Null", Grass, nullS, 0, 0, 0, 0, 0, 0};
	BulbasaurT = (PokemonType) {"Bulbasaur", Grass, bulbasaurS, 45, 49, 49, 65, 65, 45, 0};
	SquirtleT = (PokemonType) {"Squirtle", Water, squirtleS, 44, 48, 65, 50, 64, 43, 1};
	CharmanderT = (PokemonType) {"Charmander", Fire, charmanderS, 39, 52, 43, 60, 50, 65, 2};
	PidgeyT = (PokemonType) {"Pidgey", Flying, pidgeyS, 40, 45, 40, 35, 35, 56, 3};
	PikachuT = (PokemonType) {"Pikachu", Electric, pikachuS, 35, 55, 40, 50, 50, 90, 4};
	
	starters[0] = BulbasaurT;
	starters[1] = SquirtleT;
	starters[2] = CharmanderT;
	
	PokemonInstType BulbasaurStart = {2, 130, BulbasaurT.mhealth, BulbasaurT};
	PokemonInstType SquirtleStart = {44, 130, SquirtleT.mhealth, SquirtleT};
	PokemonInstType CharmanderStart = {86, 130, CharmanderT.mhealth, CharmanderT};
	
	starterInsts[0] = (SpriteInstType) {BulbasaurStart.xPos, BulbasaurStart.yPos, BulbasaurStart.species.sprite};
	starterInsts[1] = (SpriteInstType) {SquirtleStart.xPos, SquirtleStart.yPos, SquirtleStart.species.sprite};
	starterInsts[2] = (SpriteInstType) {CharmanderStart.xPos, CharmanderStart.yPos, CharmanderStart.species.sprite};
}

PokemonType DrawTitleScreen(SpriteSelectType starterScreen){
	
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
		if(isPE3Pressed()) return starters[starterScreen.currentIndex];
  }
}

void DrawWorld(PlayerType p1){
	//draws black border around the edges of the screen
	
	PokemonType allPokemon[] = {BulbasaurT, SquirtleT, CharmanderT, PidgeyT, PikachuT};
	DrawBorder(GAME_BORDER_W, GAME_BORDER_W, _width-2*GAME_BORDER_W, _height-2*GAME_BORDER_W, GAME_BORDER_W, GAME_BORDER_COLOR);
	
	while(1){
		while(ADCStatus == 0){}
			
		uint8_t xDir = getJoystickX();
		uint8_t yDir = getJoystickY();
		ADCStatus = 0;
		
		bool moved = false;
		if(xDir == 0){
			moved = MoveLeft(&p1);
		}else if(xDir == 2){
			moved = MoveRight(&p1);
		}else if(yDir == 0){
			moved = MoveUp(&p1);
		}else if(yDir == 2){
			moved = MoveDown(&p1);
		}
		
		uint8_t encounter = Random()%10;
		if(moved && encounter == 0){
			ST7735_FillScreen(0xFFFF);
			uint8_t pokemonRan = Random()%5;
			PokemonType selected = allPokemon[pokemonRan];
			DrawBattleScreen(&team[0], &selected);
			//Delay100ms(20);
		}
		DrawField(p1);
	}
}

void DrawBattleScreen(const PokemonInstType* pokeLeft, const PokemonType* pokeRight){
	ClearScreenGrid();
	ST7735_FillScreen(0xFFFF);
	SpriteInstType leftInst = (SpriteInstType) {2, 90, pokeLeft->species.sprite};
	SpriteInstType rightInst = (SpriteInstType) {86, 90, pokeRight->sprite};
	
	PokemonInstType pokemonRight = {86, 90, pokeRight->mhealth, *pokeRight};
	
	DrawSpriteImg(leftInst);
	DrawSpriteImg(rightInst);
	
	SpriteType fightText = {fight, 32, 16};
	SpriteInstType fightInst = {14, 120, fightText};
	
	SpriteType pokeText = {pokemon, 32, 16};
	SpriteInstType pokeInst = {14, 150, pokeText};
	
	SpriteType itemText = {item, 32, 16};
	SpriteInstType itemInst = {84, 120, itemText};
	
	SpriteType runText = {run, 32, 16};
	SpriteInstType runInst = {84, 150, runText};
	
	SpriteInstType battleCommands[4] = {fightInst, itemInst, pokeInst, runInst};
	SpriteSelectType battleScreen = {battleCommands, 4, 0};
	DrawAllSprites(battleScreen);
	
	ST7735_FillRect(pokeLeft->xPos+5, 45, 30, 2, 0x0000);
	ST7735_FillRect(pokemonRight.xPos+5, 45, 30, 2, 0x0000);
	
	ST7735_FillRect(pokeLeft->xPos+5, 45, pokeLeft->chealth*30/pokeLeft->species.mhealth, 2, 0x00FF);
	ST7735_FillRect(pokemonRight.xPos+5, 45, pokemonRight.chealth*30/pokemonRight.species.mhealth, 2, 0x00FF);
	
	while(1){
		
		while(ADCStatus == 0){}
			
		uint8_t xDir = getJoystickX();
		uint8_t yDir = getJoystickY();
		ADCStatus = 0;
		
		if(xDir == 2){
			if(battleScreen.currentIndex < 3) battleScreen.currentIndex = battleScreen.currentIndex + 1;
		}else if(xDir == 0){
			if(battleScreen.currentIndex > 0) battleScreen.currentIndex = battleScreen.currentIndex - 1;
		}else if(yDir == 2){
			if(battleScreen.currentIndex < 2) battleScreen.currentIndex = battleScreen.currentIndex + 2;
		}else if(yDir == 0){
			if(battleScreen.currentIndex > 1) battleScreen.currentIndex = battleScreen.currentIndex - 2;
		}
		
		DrawSelection(&battleScreen, 0x0000, 0xFFFF, 1);
		if(isPE3Pressed()){
			if(battleScreen.currentIndex == 3){
				break;
			}else if(battleScreen.currentIndex == 0){
				DrawMoveCommands(pokeLeft, &pokemonRight);
				DrawAllSprites(battleScreen);
			}
		}
  }
}

void DrawMoveCommands(const PokemonInstType* pokeLeft, const PokemonInstType* pokeRight){
	
	ST7735_FillRect(10, 104, 106, 46, 0xFFFF);
	MoveType normal = NormalMoves[pokeLeft->species.moveSet];
	MoveType signature = SignatureMoves[pokeLeft->species.moveSet];
	uint8_t selected = 0;
	char *a[3];
	a[0] = normal.name;
	a[1] = signature.name;
	a[2] = "back";
	
	for(int i=0; i<3; i++){
			ST7735_SetCursor(3, 12+i);
			ST7735_OutString(a[i]);
	}
	while(1){
		while(ADCStatus == 0){}
			
		uint8_t yDir = getJoystickY();
		ADCStatus = 0;
		
		if(yDir == 2 && selected < 2){
			selected++;
		}else if(yDir == 0 && selected > 0){
			selected--;
		}
		
		for(int i=0; i<3; i++){
			ST7735_SetCursor(1, 12+i);
			if(i==selected) ST7735_OutString("*");
			else ST7735_OutString(" ");
		}
		
		if(isPE3Pressed()){
			MoveType selectedMove;
			if(selected == 0){
				selectedMove = normal;
			}else if(selected == 1){
				selectedMove = signature;
			}else{
				ST7735_FillRect(0, 104, 116, 46, 0xFFFF);
				break;
			}
			ST7735_FillRect(0, 104, 116, 46, 0xFFFF);
			ST7735_SetCursor(1, 12);
			ST7735_OutString(pokeLeft->species.name);
			ST7735_OutString(" used \n ");
			ST7735_OutString(selectedMove.name);
			while(1) {if(isPE3Pressed()) break;}
			
			ST7735_FillRect(0, 104, 116, 46, 0xFFFF);
			uint8_t effectiveness = TypesArray[selectedMove.type][pokeRight->species.type];
			ST7735_SetCursor(1, 12);
			if(effectiveness == A){
				ST7735_OutString("Very effective!");
			}else if(effectiveness == C){
				ST7735_OutString("Not very effective.");
			}else if(effectiveness == D){
				ST7735_OutString("No effect...");
			}
			
			while(1) {if(isPE3Pressed()) break;}
			
			ST7735_FillRect(0, 104, 116, 46, 0xFFFF);
		
			break;
		}
	}
}
