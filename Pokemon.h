
#ifndef _POKEMONH_
#define _POKEMONH_

#include <stdint.h>
#include "Draw.h"
#include "PokemonType.h"

typedef struct Pokemon PokemonType;
typedef struct PokemonInst PokemonInstType;

struct Pokemon {
	const char *name;
	const uint8_t type;
	const SpriteType sprite;
};

struct PokemonInst {
	uint16_t xPos;
	uint16_t yPos;
	const PokemonType species;
	uint32_t mhealth;
	uint32_t chealth;
	uint32_t attack;
	uint32_t defense;
	uint32_t spattack;
	uint32_t spdefense;
	uint32_t speed;
};

extern PokemonType Bulbasaur;
extern PokemonType Squirtle;
extern PokemonType Charmander;

#endif
