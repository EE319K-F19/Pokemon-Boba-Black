
#include <stdbool.h>
#include "Field.h"
#include "ImagesOther.h"
#include "Player.h"
#include "Shop.h"
#include "ST7735.h"
#include "StructDec.h"
#include "SystemInfo.h"

PlayerType p1;
ItemInventoryType playerInventory[3];
PokemonInstType* playerTeam;

void InitPlayer(){
	SpriteType PlayerFront = {playerFront, 16, 16};
	SpriteType PlayerBack = {playerBack, 16, 16};
	SpriteType PlayerSide = {playerSide, 16, 16};
	SpriteType PlayerSideFlipped = {playerSideFlipped, 16, 16};
	p1 = (PlayerType) {10, 10, PlayerFront, PlayerFront, PlayerBack, PlayerSide, PlayerSideFlipped, 0, 25};
}

void InitInventory(){
	playerInventory[0] = (ItemInventoryType) {pokeballItem, 0};
	playerInventory[1] = (ItemInventoryType) {potionItem, 0};
	playerInventory[2] = (ItemInventoryType) {bobaItem, 0};
}

void InitTeam(PokemonInstType* starterTeam){
	playerTeam = starterTeam;
}

void DrinkBoba(){
	p1.happiness += 25;
}

void LoseBattle(){
	p1.happiness -= 10;
}

bool MoveUp(){
	p1.sprite = p1.spriteBack;
	if(IsWalkable(p1.YPos-1, p1.XPos)){
		p1.YPos --;
		return true;
	}
	return false;
}

bool MoveDown(){
	p1.sprite = p1.spriteFront;
	if(IsWalkable(p1.YPos+1, p1.XPos)){
		p1.YPos ++;
		return true;
	}
	return false;
}

bool MoveLeft(){
	p1.sprite = p1.spriteLeft;
	if(IsWalkable(p1.YPos, p1.XPos-1)){
		p1.XPos --;
		return true;
	}
	return false;
}

bool MoveRight(){
	p1.sprite = p1.spriteSide;
	if(IsWalkable(p1.YPos, p1.XPos+1)){
		p1.XPos ++;
		return true;
	}
	return false;
}
