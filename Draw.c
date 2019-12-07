
#include <stdint.h>
#include "Draw.h"
#include "ST7735.h"
#include "SystemInfo.h"

uint8_t pokeBattleLeftX = 2;
uint8_t pokeBattleRightX = 86;
uint8_t pokeBattleY = 90;

void ClearScreenWhite(){
	ST7735_FillScreen(0xFFFF);
}

void ClearScreenBlack(){
	ST7735_FillScreen(0x0000);
}

void ClearBattleUI(){
	uint8_t uiY = 100;
	ST7735_FillRect(0, uiY, _width, _height-uiY, 0xFFFF);
}

void ClearPokeLeftName(){
	ST7735_FillRect(0, 0, 72, 30, 0xFFFF);
}

void DrawBorder(uint16_t itemX, uint16_t itemY, uint16_t itemW, uint16_t itemH, uint8_t borderW, uint16_t borderColor){
	uint16_t borderXStart = itemX - borderW;
	uint16_t borderYStart = itemY - borderW;
	uint16_t borderXLength = itemW + borderW;
	uint16_t borderYLength = itemH + borderW;
	
	ST7735_FillRect(borderXStart, borderYStart, borderXLength, borderW, borderColor);
	ST7735_FillRect(borderXStart, borderYStart+borderW, borderW, borderYLength, borderColor);	
	ST7735_FillRect(borderXStart+borderW, borderYStart+borderYLength, borderXLength, borderW, borderColor);
	ST7735_FillRect(borderXStart+borderXLength, borderYStart, borderW, borderYLength, borderColor);
}


void DrawSelection(SpriteSelectType *starterSelect, uint16_t selectColor, uint16_t deselectColor, uint8_t selectWidth){
	for(int i=0; i<starterSelect->spriteArrayLength; i++){
		if(i == starterSelect->currentIndex){
			DrawSpriteSelection(starterSelect->spriteInsts[i], selectWidth, selectColor);
		}else {
			DrawSpriteSelection(starterSelect->spriteInsts[i], selectWidth, deselectColor);
		}
	}
}

void DrawSpriteInstSelection(SpriteInstType spriteInst, uint8_t width, uint16_t color){
	DrawBorder(spriteInst.x_left, spriteInst.y_bottom-spriteInst.sprite.height+1, spriteInst.sprite.width, spriteInst.sprite.height, width, color);
}

void DrawSpriteSelection(SpriteInstType spriteInst, uint8_t width, uint16_t color){
	DrawBorder(spriteInst.x_left, spriteInst.y_bottom-spriteInst.sprite.height+1, spriteInst.sprite.width, spriteInst.sprite.height, width, color);
}

void DrawGridSprite(uint8_t column, uint8_t row, SpriteType sprite){
	ST7735_DrawBitmap(GetGridX(column), GetGridY(row+1)-1, sprite.image, sprite.width, sprite.height);
}

void DrawGridFill(uint8_t column, uint8_t row, uint16_t color){
	ST7735_FillRect(GetGridX(column), GetGridY(row), GRID_LENGTH, GRID_LENGTH, color);
}

void DrawAllSprites(SpriteSelectType selection){
	for(int i=0; i<selection.spriteArrayLength; i++){
			DrawSpriteImg(selection.spriteInsts[i]);
	}
}

void DrawSpriteImg(SpriteInstType spriteInst){
	ST7735_DrawBitmap(spriteInst.x_left, spriteInst.y_bottom, spriteInst.sprite.image, spriteInst.sprite.width, spriteInst.sprite.height);
}

uint16_t GetGridX(uint8_t column){
	return GAME_BORDER_W + column*GRID_LENGTH;
}

uint16_t GetGridY(uint8_t row){
	return GAME_BORDER_W + row*GRID_LENGTH;
}

void DrawHPBars(PokemonInstType* pokeLeft, PokemonInstType* pokeRight){
	uint32_t lowColor = 0x00FF;
	uint32_t highColor = 0x0FF0;
	
	uint32_t lColor = highColor;
	uint32_t rColor = highColor;
	
	if(pokeLeft->chealth <= pokeLeft->species.mhealth/2) lColor = lowColor;
	if(pokeRight->chealth <= pokeRight->species.mhealth/2) rColor = lowColor;
	
	ST7735_FillRect(pokeBattleLeftX+5, 35, 30, 2, 0x0000);
	ST7735_FillRect(pokeBattleRightX+5, 25, 30, 2, 0x0000);
	
	ST7735_FillRect(pokeBattleLeftX+5, 35, pokeLeft->chealth*30/pokeLeft->species.mhealth, 2, lColor);
	ST7735_FillRect(pokeBattleRightX+5, 25, pokeRight->chealth*30/pokeRight->species.mhealth, 2, rColor);
}

void DrawEPBars(PokemonInstType* pokeLeft, PokemonInstType* pokeRight){
	ST7735_FillRect(pokeBattleLeftX+5, 40, 30, 2, 0x0000);
	ST7735_FillRect(pokeBattleRightX+5, 30, 30, 2, 0x0000);
	
	ST7735_FillRect(pokeBattleLeftX+5, 40, pokeLeft->cenergy*30/pokeLeft->species.menergy, 2, 0xFF00);
	ST7735_FillRect(pokeBattleRightX+5, 30, pokeRight->cenergy*30/pokeRight->species.menergy, 2, 0xFF00);
}

void DrawPokemonNames(PokemonInstType* pokeLeft, PokemonInstType* pokeRight){
	
	ClearPokeLeftName();
	ST7735_SetCursor(1, 2);
	ST7735_OutString(pokeLeft->species.name);
	
	uint8_t length = 0;
	while(pokeRight->species.name[length] != 0x0000){
		length++;
	}
	
	ST7735_SetCursor(20-length, 4);
	ST7735_OutString(pokeRight->species.name);
}
