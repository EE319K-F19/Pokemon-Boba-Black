
#include "Player.h"
#include "Field.h"

void DrawSpriteImgPlayer(PlayerType player){
	ST7735_DrawBitmap(player.XPos*16, player.YPos*16+player.sprite->height, player.sprite->image, player.sprite->width, player.sprite->height);
}

void MoveUp(PlayerType *player){
	player->sprite = player->spriteBack;
	if(IsWalkable(player->YPos-1, player->XPos)){
		player->YPos --;
	}
}

void MoveDown(PlayerType *player){
	player->sprite = player->spriteFront;
	if(IsWalkable(player->YPos+1, player->XPos)){
		player->YPos ++;
	}
}

void MoveLeft(PlayerType *player){
	player->sprite = player->spriteLeft;
	if(IsWalkable(player->YPos, player->XPos-1)){
		player->XPos --;
	}
}

void MoveRight(PlayerType *player){
	player->sprite = player->spriteSide;
	if(IsWalkable(player->YPos-1, player->XPos)){
		player->XPos ++;
	}
}
