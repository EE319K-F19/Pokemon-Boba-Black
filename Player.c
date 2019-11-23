
#include "Player.h"

void DrawSpriteImgPlayer(PlayerType player){
	ST7735_DrawBitmap(player.XPos*16, player.YPos*16+player.sprite->height, player.sprite->image, player.sprite->width, player.sprite->height);
}

void MoveUp(PlayerType *player){
	player->spriteSide->reverse = 0;
	player->sprite = player->spriteBack;
	player->spriteFlip = 0;
	player->YPos --;
}

void MoveDown(PlayerType *player){
	player->spriteSide->reverse = 0;
	player->sprite = player->spriteFront;
	player->spriteFlip = 0;
	player->YPos ++;
}

void MoveLeft(PlayerType *player){
	player->spriteSide->reverse = 1;
	player->sprite = player->spriteSide;
	player->spriteFlip = 1;
	player->XPos --;
}

void MoveRight(PlayerType *player){
	player->spriteSide->reverse = 0;
	player->sprite = player->spriteSide;
	player->spriteFlip = 0;
	player->XPos ++;
}
