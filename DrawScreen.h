
#ifndef _DRAWSCREENH_
#define _DRAWSCREENH_

#include <stdbool.h>
#include <stdint.h>
#include "StructDec.h"

void InitPokemon(void);
PokemonType DrawTitleScreen(void);
void DrawBattleScreen(PokemonInstType* pokeLeft, const PokemonType* pokeRight);
bool DrawWorld(void);
uint8_t DrawMoveCommands(PokemonInstType* pokeLeft, PokemonInstType* pokeRight);
void InitInventory(void);
void DrawBattleInventory(PokemonInstType* pokeLeft, PokemonInstType* pokeRight);
void TakeDamage(SpriteInstType dmgPokemon, bool moveLeft);

#endif
