
#include <stdint.h>
#include "ST7735.h"
#include "SystemInfo.h"
#include "Draw.h"

void DrawBorder(uint16_t itemX, uint16_t itemY, uint16_t itemW, uint16_t itemH, uint8_t borderW, uint16_t borderColor){
	uint16_t borderXStart = itemX - borderW;
	uint16_t borderYStart = itemY - borderW;
	uint16_t borderXLength = itemW + borderW;
	uint16_t borderYLength = itemH + borderW;
	
	ST7735_FillRect(borderXStart, borderXStart, borderXLength, borderW, borderColor);
	ST7735_FillRect(borderXStart, borderYStart+borderW, borderW, borderYLength, borderColor);	
	ST7735_FillRect(borderXStart+borderW, borderYStart+borderYLength, borderXLength, borderW, borderColor);
	ST7735_FillRect(borderXStart+borderXLength, borderYStart, borderW, borderYLength, borderColor);
}

void DrawGridSprite(uint8_t column, uint8_t row, SpriteType sprite){
	ST7735_DrawBitmap(GetGridX(column), GetGridY(row+1)-1, sprite.image, sprite.width, sprite.height);
}

void DrawGridFill(uint8_t column, uint8_t row, uint16_t color){
	ST7735_FillRect(GetGridX(column), GetGridY(row), GRID_LENGTH, GRID_LENGTH, color);
}

uint16_t GetGridX(uint8_t column){
	return GAME_BORDER_W + column*GRID_LENGTH;
}

uint16_t GetGridY(uint8_t row){
	return GAME_BORDER_W + row*GRID_LENGTH;
}

void DrawStartScreen(SpriteSelectType *starterSelect){
	for(int i=0; i<3; i++){
		if(i == starterSelect->currentIndex){
			DrawSpriteSelectionDefault(starterSelect->sprites[i]);
		}else {
			DrawSpriteImg(starterSelect->sprites[i]);
		}
	}
	nextIndex(starterSelect);
	Delay10ms(10); 
}

void DrawSpriteImg(SpriteInstanceType spriteInst){
	ST7735_DrawBitmap(spriteInst.x_left, spriteInst.y_bottom, spriteInst.sprite.image, spriteInst.sprite.width, spriteInst.sprite.height);
}


void DrawSpriteSelection(SpriteInstanceType spriteInst, uint8_t width, uint16_t color){
	ST7735_FillRect(spriteInst.x_left-width, 
		spriteInst.y_bottom-spriteInst.sprite.height-width, spriteInst.sprite.width+width*2, spriteInst.sprite.height+width*3, color);
	DrawSpriteImg(spriteInst);
}

void DrawSpriteSelectionDefault(SpriteInstanceType spriteInst){
	DrawSpriteSelection(spriteInst, 1, 0x0F6F);
}

void nextIndex(SpriteSelectType *selectType){
	uint8_t index = (selectType->currentIndex + 1) % selectType->spriteArrayLength;
	selectType->currentIndex = index;
}

//must remove these delay functions and replace with interrupts

void Delay100ms(uint32_t count){uint32_t volatile time;
  while(count>0){
    time = 727240;  // 0.1sec at 80 MHz
    while(time){
	  	time--;
    }
    count--;
  }
}

void Delay10ms(uint32_t count){uint32_t volatile time;
  while(count>0){
    time = 727240/10;  // 0.1sec at 80 MHz
    while(time){
	  	time--;
    }
    count--;
  }
}