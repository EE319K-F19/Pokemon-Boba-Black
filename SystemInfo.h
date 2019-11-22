
#ifndef _SYSTEMINFOH_
#define _SYSTEMINFOH_

#include <stdint.h>

extern int16_t _width; 	//width of screen in pixels
extern int16_t _height; //height of screen in pixels

extern const uint8_t GRID_LENGTH;	//pixels per grid

/*return the number of columns on the screen: _width/GRID_LENGTH*/
uint32_t GetScreenColumns(void);
/*return the number of rows on the screen: _height/GRID_LENGTH*/
uint32_t GetScreenRows(void);

#endif
