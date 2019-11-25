
#include "DrawScreen.h"
#include "ST7735.h"

#include "ADC_Joystick.h"
#include "Field.h"
#include "PokemonType.h"
#include "SystemInfo.h"

#include "TextSprites.h"
#include "ImagesPokemon2.h"

PokemonType BulbasaurT;
PokemonType SquirtleT;
PokemonType CharmanderT;

void InitPokemon(){
	SpriteType bulbasaurS = {bulbasaur, 40, 40};
	SpriteType squirtleS = {squirtle, 40, 40};
	SpriteType charmanderS = {charmander, 40, 40};
	BulbasaurT = (PokemonType) {"Bulbasaur", Grass, bulbasaurS, 45, 49, 49, 65, 65, 45};
	SquirtleT = (PokemonType) {"Squirtle", Water, squirtleS, 44, 48, 65, 50, 64, 43};
	CharmanderT = (PokemonType) {"Charmander", Fire, charmanderS, 39, 52, 43, 60, 50, 65};
}

void DrawBattleScreen(PokemonInstType* pokeLeft, PokemonInstType* pokeRight){
	ST7735_FillScreen(0xFFFF);
	SpriteInstType leftInst = (SpriteInstType) {2, 90, pokeLeft->species.sprite};
	SpriteInstType rightInst = (SpriteInstType) {86, 90, pokeRight->species.sprite};
	
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
	ST7735_FillRect(pokeRight->xPos+5, 45, 30, 2, 0x0000);
	
	ST7735_FillRect(pokeLeft->xPos+5, 45, pokeLeft->chealth*30/pokeLeft->species.mhealth, 2, 0x00FF);
	ST7735_FillRect(pokeRight->xPos+5, 45, pokeRight->chealth*30/pokeRight->species.mhealth, 2, 0x00FF);
	
	//while(1){
		
		//while(ADCStatus == 0){}
			
		//uint8_t xDir = getJoystickX();
		//uint8_t yDir = getJoystickY();
		//ADCStatus = 0;
		
		//if(xDir == 2){
			//if(battleScreen.currentIndex < 3) battleScreen.currentIndex = battleScreen.currentIndex + 1;
		//}else if(xDir == 0){
			//if(battleScreen.currentIndex > 0) battleScreen.currentIndex = battleScreen.currentIndex - 1;
		//}else if(yDir == 2){
			//if(battleScreen.currentIndex < 2) battleScreen.currentIndex = battleScreen.currentIndex + 2;
		//}else if(yDir == 0){
			//if(battleScreen.currentIndex > 1) battleScreen.currentIndex = battleScreen.currentIndex - 2;
		//}
			
		//DrawSelection(&battleScreen, 0x0000, 0xFFFF, 1);
		//Delay100ms(2);
  //}
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

void DrawWorld(PlayerType p1, FieldType mainField){
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

