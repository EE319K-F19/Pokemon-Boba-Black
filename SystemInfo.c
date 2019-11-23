
#include <stdint.h>
#include "ST7735.h"

#include "SystemInfo.h"

int16_t _width = ST7735_TFTWIDTH;   					
int16_t _height = ST7735_TFTHEIGHT;
const uint8_t GRID_LENGTH = 16;
const uint8_t GAME_BORDER_W = 8;
const uint16_t GAME_BORDER_COLOR = 0x0000;

const int16_t SCREEN_COLUMNS = (128-2*GAME_BORDER_W)/GRID_LENGTH;
const int16_t SCREEN_ROWS = (160-2*GAME_BORDER_W)/GRID_LENGTH;
const uint8_t SCREEN_MID_COL = SCREEN_COLUMNS / 2;
const uint8_t SCREEN_MID_ROW = SCREEN_ROWS / 2;
