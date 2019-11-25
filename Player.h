
#ifndef _PLAYERH_
#define _PLAYERH_

#include <stdint.h>
#include "ST7735.h"

#include "SpaceInvaders.h"
#include "Shop.h"

typedef struct Player PlayerType;
typedef struct ItemInventory ItemInventoryType;

struct Player {
	uint32_t XPos;
	uint32_t YPos;
	
	SpriteType *sprite;
	SpriteType *spriteFront;
	SpriteType *spriteBack;
	SpriteType *spriteSide;
	SpriteType *spriteLeft;
	uint32_t coins;
	uint32_t happiness;
	
	//PokemonInstType *PokemonTeam;
	// ItemInventoryType playerInventory[3];
};


void DrawSpriteImgPlayer(PlayerType player);

void MoveUp(PlayerType *player);
void MoveDown(PlayerType *player);
void MoveLeft(PlayerType *player);
void MoveRight(PlayerType *player);

#endif
