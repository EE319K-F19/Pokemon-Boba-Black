
#include <stdint.h>
#include "ST7735.h"
#include "SystemInfo.h"
#include "Draw.h"
#include "SpaceInvaders.h"

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

//must remove these delay functions and replace with interrupts

void Delay10ms(uint32_t count){uint32_t volatile time;
  while(count>0){
    time = 727240/10;  // 0.1sec at 80 MHz
    while(time){
	  	time--;
    }
    count--;
  }
}

void Delay100ms(uint32_t count){uint32_t volatile time;
  while(count>0){
    time = 727240;  // 0.1sec at 80 MHz
    while(time){
	  	time--;
    }
    count--;
  }
}
