
#ifndef _SYSTEMINFOH_
#define _SYSTEMINFOH_

#include <stdint.h>

extern int16_t _width; 								//width of screen in pixels
extern int16_t _height; 							//height of screen in pixels
extern const uint8_t GRID_LENGTH;			//pixels per grid
extern const uint8_t GAME_BORDER_W; 	//width of border around the game
extern const uint16_t GAME_BORDER_COLOR;

extern const int16_t SCREEN_COLUMNS;
extern const int16_t SCREEN_ROWS;
extern const uint8_t SCREEN_MID_COL;
extern const uint8_t SCREEN_MID_ROW;

#endif
