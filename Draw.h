
#ifndef _DRAWH_
#define _DRAWH_


#include <stdint.h>

void Delay10ms(uint32_t count);
void Delay100ms(uint32_t count);

typedef struct Sprite SpriteType;
typedef struct SpriteInstance SpriteInstanceType;
typedef struct SpriteSelect SpriteSelectType;

uint16_t GetGridX(uint8_t column);
uint16_t GetGridY(uint8_t row);
void DrawBorder(uint16_t itemX, uint16_t itemY, uint16_t itemW, uint16_t itemH, uint8_t borderW, uint16_t borderColor);
void DrawStartScreen(SpriteSelectType *starterSelect);
void DrawSpriteImg(SpriteInstanceType sprite);
void DrawSpriteSelection(SpriteInstanceType sprite, uint8_t width, uint16_t color);
void DrawSpriteSelectionDefault(SpriteInstanceType sprite);
void DrawGridFill(uint8_t column, uint8_t row, uint16_t color);
void DrawGridSprite(uint8_t column, uint8_t row, SpriteType sprite);
void nextIndex(SpriteSelectType *selectType);

struct Sprite {
	const uint16_t *image;	
	int16_t width; 
	int16_t height;
};

struct SpriteInstance {
	int16_t x_left; 
	int16_t y_bottom;
	const SpriteType sprite;
};


struct SpriteSelect {
	SpriteInstanceType *sprites;
	uint16_t spriteArrayLength;
	int16_t currentIndex;
};

#endif
