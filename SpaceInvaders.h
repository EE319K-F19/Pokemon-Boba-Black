
#ifndef _SPACEINVADERSH_
#define _SPACEINVADERSH_

#include <stdint.h>
#include "Draw.h"
#include "PokemonType.h"
#include "Shop.h"

typedef struct Pokemon PokemonType;
typedef struct PokemonInst PokemonInstType;

struct Pokemon {
	char *name;
	uint8_t type;
	SpriteType sprite;
	uint32_t mhealth;
	uint32_t attack;
	uint32_t defense;
	uint32_t spattack;
	uint32_t spdefense;
	uint32_t speed;
};

struct PokemonInst {
	uint16_t xPos;
	uint16_t yPos;
	uint32_t chealth;
	const PokemonType species;
};

extern PokemonType BulbasaurT;
extern PokemonType SquirtleT;
extern PokemonType CharmanderT;

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts

// void DrawShopScreen(SpriteSelectType shopScreen, const ItemInstType shopItems[3]);

void DrawTitleScreen(SpriteSelectType starterScreen);
void DrawWorld(void);
void InitDrawScreen(void);
void DrawBattleScreen(PokemonInstType* pokeLeft, PokemonInstType* pokeRight);
uint16_t* GetReverseXImage(const uint16_t *image, uint8_t w, uint8_t h);

#endif
