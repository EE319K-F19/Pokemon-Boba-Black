
#include <stdint.h>
#include "ST7735.h"

#include "SystemInfo.h"

int16_t _width = ST7735_TFTWIDTH;   // this could probably be a constant, except it is used in Adafruit_GFX and depends on image rotation
int16_t _height = ST7735_TFTHEIGHT;
const uint8_t GRID_LENGTH = 32;

uint32_t GetScreenColumns(){
	return _width/GRID_LENGTH;
}

uint32_t GetScreenRows(){
	return _height/GRID_LENGTH;
}
