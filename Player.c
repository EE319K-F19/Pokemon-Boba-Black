
#include "Player.h"

void DrawSpriteImgPlayer(PlayerType player){
	ST7735_DrawBitmap(player.XPos*16, player.YPos*16+player.sprite->height, player.sprite->image, player.sprite->width, player.sprite->height);
}