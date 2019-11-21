
#include <stdint.h>
#include "ST7735.h"
#include "Draw.h"

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