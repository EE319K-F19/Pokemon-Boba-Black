
#include <stdint.h>
#include "ST7735.h"
#include "Random.h"

#include "ADC_Joystick.h"
#include "Draw.h"
#include "DrawScreen.h"
#include "Field.h"
#include "ImagesPokemon2.h"
#include "Player.h"
#include "PokemonType.h"
#include "SystemInfo.h"
#include "TextSprites.h"

PokemonType NullT;
PokemonType BulbasaurT;
PokemonType SquirtleT;
PokemonType CharmanderT;
PokemonType PidgeyT;
PokemonType PikachuT;
PlayerType p1;

void InitPokemon(){
	uint16_t nullSprite[1] = {0x0000};
	SpriteType nullS = {nullSprite, 1, 1};
	SpriteType bulbasaurS = {bulbasaur, 40, 40};
	SpriteType squirtleS = {squirtle, 40, 40};
	SpriteType charmanderS = {charmander, 40, 40};
	SpriteType pidgeyS = {pidgey, 40, 40};
	SpriteType pikachuS = {pikachu, 40, 40};
	
	NullT = (PokemonType) {"Null", Grass, nullS, 0, 0, 0, 0, 0, 0};
	BulbasaurT = (PokemonType) {"Bulbasaur", Grass, bulbasaurS, 45, 49, 49, 65, 65, 45};
	SquirtleT = (PokemonType) {"Squirtle", Water, squirtleS, 44, 48, 65, 50, 64, 43};
	CharmanderT = (PokemonType) {"Charmander", Fire, charmanderS, 39, 52, 43, 60, 50, 65};
	PidgeyT = (PokemonType) {"Pidgey", Flying, pidgeyS, 40, 45, 40, 35, 35, 56};
	PikachuT = (PokemonType) {"Pikachu", Electric, pikachuS, 35, 55, 40, 50, 50, 90};
	
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

void DrawWorld(PlayerType p1, FieldType mainField){
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
			//DrawBattleScreen(&pokemonTeam.pokemon1, &selected);
			Delay100ms(20);
		}
		DrawField(p1, mainField);
	}
}

void DrawBattleScreen(const PokemonInstType* pokeLeft, PokemonType* pokeRight){
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
		if(isPE3Pressed() && battleScreen.currentIndex == 3){
			break;
		}
  }
}

