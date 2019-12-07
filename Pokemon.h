
#ifndef _POKEMONH_
#define _POKEMONH_

#include <stdint.h>
#include "PokemonType.h"

extern PokemonType BulbasaurT;
extern PokemonType SquirtleT;
extern PokemonType CharmanderT;

extern PokemonType allPokemon[20];
extern uint32_t numPokemonSpecies;
void InitPokemon(void);

#endif
