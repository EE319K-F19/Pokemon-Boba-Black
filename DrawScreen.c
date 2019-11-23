
#include "DrawScreen.h"
#include "ADC_Joystick.h"
#include "ImagesPokemon.h"
#include "Battle.h"
#include "Field.h"
#include "ImagesOther.h"
#include "SystemInfo.h"

uint8_t ADCStatus = 0;

static PlayerType p1;
FieldType mainField = {fieldArray, 64, 40};
static SpriteSelectType starterScreen;

void InitDrawScreen(){
	const SpriteType Bulbasaur = {bulbasaur, 40, 40};
	const SpriteType Charmander = {charmander, 40, 40};
	const SpriteType Squirtle = {squirtle, 40, 40};

	const SpriteType PlayerFront = {playerFront, 16, 16};
	const SpriteType PlayerBack = {playerBack, 16, 16};
	const SpriteType PlayerSide = {playerSide, 16, 16};
	
	SpriteInstanceType poke1 = {2, 130, Bulbasaur};
  SpriteInstanceType poke2 = {44, 130, Charmander};
  SpriteInstanceType poke3 = {86, 130, Squirtle};
  SpriteInstanceType starters[3] = {poke1, poke2, poke3};
	starterScreen = (SpriteSelectType) {starters, 3, 1};
	
	p1 = (PlayerType) {SCREEN_MID_COL, SCREEN_MID_ROW, &PlayerFront, &PlayerFront, &PlayerBack, &PlayerSide, 0};
	
	ST7735_FillScreen(0xFFFF);
	//draws black border around the edges of the screen
	DrawBorder(GAME_BORDER_W, GAME_BORDER_W, _width-2*GAME_BORDER_W, _height-2*GAME_BORDER_W, GAME_BORDER_W, GAME_BORDER_COLOR);
}

void DrawTitleScreen(){
	DrawAllSprites(starterScreen.sprites, starterScreen.spriteArrayLength);
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
		
		if(xDir == 2){
			starterScreen.currentIndex = (starterScreen.currentIndex + 1)%3;
		}else if(xDir == 0){
			starterScreen.currentIndex = starterScreen.currentIndex - 1;
			if(starterScreen.currentIndex < 0) starterScreen.currentIndex = 2;
		}
			
		DrawSelection(&starterScreen, 0x0000, 0xFFFF, 1);
		ADCStatus = 0;
		Delay100ms(2);
  }
}

void DrawWorld(){
		//if(xDir == 0){
			//MoveLeft(&p1);
		//}else if(xDir == 2){
			//MoveRight(&p1);
		//}else if(yDir == 0){
			//MoveUp(&p1);
		//}else if(yDir == 2){
			//MoveDown(&p1);
		//}
		
		//DrawField(p1, mainField);
	
		//DrawSpriteImgPlayer(p1);
		//p1.XPos++;
		//DrawSpriteImg()
		//mainField.XPos ++;
		//p1.XPos++;
}

