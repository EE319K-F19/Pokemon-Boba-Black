
#include <stdbool.h>
#include "Field.h"
#include "Player.h"
#include "ST7735.h"
#include "StructDec.h"
#include "ImagesOther.h"
#include "SystemInfo.h"

PlayerType p1;

void InitPlayer(){
	SpriteType PlayerFront = {playerFront, 16, 16};
	SpriteType PlayerBack = {playerBack, 16, 16};
	SpriteType PlayerSide = {playerSide, 16, 16};
	SpriteType PlayerSideFlipped = {playerSideFlipped, 16, 16};
	p1 = (PlayerType) {SCREEN_MID_COL+5, SCREEN_MID_ROW+5, PlayerFront, PlayerFront, PlayerBack, PlayerSide, PlayerSideFlipped, 0, 25};
	
	SpriteInstType pokeballInst = (SpriteInstType) {2, 142, pokeball};
	SpriteInstType potionInst = (SpriteInstType) {44, 142, healthPotion};
	SpriteInstType bobaInst = (SpriteInstType) {86, 142, boba};
}

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
