
#ifndef _PLAYERH_
#define _PLAYERH_

#include <stdint.h>
#include "ST7735.h"

#include "Pokemon.h"

typedef struct Item ItemType;
typedef struct ItemInventory ItemInventoryType;
typedef struct Player PlayerType;

struct Player {
	uint32_t XPos;
	uint32_t YPos;
	//PokemonInstType *PokemonTeam;
	
	const SpriteType *sprite;
	const SpriteType *spriteFront;
	const SpriteType *spriteBack;
	const SpriteType *spriteSide;
	uint8_t spriteFlip;
};

struct Item {
	char* name;
	SpriteType sprite;
};

struct ItemInventory {
	ItemType item;
	uint32_t count;
};

void DrawSpriteImgPlayer(PlayerType player);

void MoveUp(PlayerType *player);
void MoveDown(PlayerType *player);
void MoveLeft(PlayerType *player);
void MoveRight(PlayerType *player);

#endif
