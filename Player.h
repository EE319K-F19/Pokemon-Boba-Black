
#ifndef _PLAYERH_
#define _PLAYERH_

#include <stdint.h>
#include "ST7735.h"

#include "SpaceInvaders.h"

typedef struct Item ItemType;
typedef struct ItemInventory ItemInventoryType;
typedef struct Player PlayerType;

struct Item {
	char* name;
	SpriteType sprite;
	uint32_t price;
	uint32_t index;
};

struct ItemInventory {
	ItemType item;
	uint32_t count;
};


struct Player {
	uint32_t XPos;
	uint32_t YPos;
	//PokemonInstType *PokemonTeam;
	
	SpriteType *sprite;
	SpriteType *spriteFront;
	SpriteType *spriteBack;
	SpriteType *spriteSide;
	SpriteType *spriteLeft;
	uint8_t spriteFlip;
	uint32_t coins;
	uint32_t happiness;
	ItemInventoryType playerInventory[3];
};


void DrawSpriteImgPlayer(PlayerType player);

void MoveUp(PlayerType *player);
void MoveDown(PlayerType *player);
void MoveLeft(PlayerType *player);
void MoveRight(PlayerType *player);

#endif
