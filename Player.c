
#include <stdbool.h>
#include "Field.h"
#include "Player.h"
#include "ST7735.h"
#include "StructDec.h"

void DrawSpriteImgPlayer(PlayerType player){
	ST7735_DrawBitmap(player.XPos*16, player.YPos*16+player.sprite.height, player.sprite.image, player.sprite.width, player.sprite.height);
}

bool MoveUp(PlayerType *player){
	player->sprite = player->spriteBack;
	if(IsWalkable(player->YPos-1, player->XPos)){
		player->YPos --;
		return true;
	}
	return false;
}

bool MoveDown(PlayerType *player){
	player->sprite = player->spriteFront;
	if(IsWalkable(player->YPos+1, player->XPos)){
		player->YPos ++;
		return true;
	}
	return false;
}

bool MoveLeft(PlayerType *player){
	player->sprite = player->spriteLeft;
	if(IsWalkable(player->YPos, player->XPos-1)){
		player->XPos --;
		return true;
	}
	return false;
}

bool MoveRight(PlayerType *player){
	player->sprite = player->spriteSide;
	if(IsWalkable(player->YPos, player->XPos+1)){
		player->XPos ++;
		return true;
	}
	return false;
}
