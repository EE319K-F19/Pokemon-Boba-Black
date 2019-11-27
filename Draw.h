
#ifndef _DRAWH_
#define _DRAWH_

#include <stdint.h>
#include "StructDec.h"

void DrawBorder(uint16_t itemX, uint16_t itemY, uint16_t itemW, uint16_t itemH, uint8_t borderW, uint16_t borderColor);
void DrawSelection(SpriteSelectType *starterSelect, uint16_t selectColor, uint16_t deselectColor, uint8_t selectWidth);
void DrawSpriteSelection(SpriteInstType spriteInst, uint8_t width, uint16_t color);
void DrawGridSprite(uint8_t column, uint8_t row, SpriteType sprite);
void DrawGridFill(uint8_t column, uint8_t row, uint16_t color);
void DrawAllSprites(SpriteSelectType selection);
void DrawSpriteImg(SpriteInstType sprite);
uint16_t GetGridX(uint8_t column);
uint16_t GetGridY(uint8_t row);

void Delay10ms(uint32_t count);
void Delay100ms(uint32_t count);

#endif
