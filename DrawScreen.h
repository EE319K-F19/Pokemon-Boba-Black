
#ifndef _DRAWSCREENH_
#define _DRAWSCREENH_

#include <stdbool.h>
#include <stdint.h>
#include "StructDec.h"

void InitPokemon(void);
PokemonType DrawTitleScreen(uint8_t language);
void DrawBattleScreen(PokemonInstType* pokeLeft, const PokemonType* pokeRight, uint8_t language);
bool DrawWorld(uint8_t language);
uint8_t DrawMoveCommands(PokemonInstType* pokeLeft, PokemonInstType* pokeRight, uint8_t language);
void InitInventory(void);
void DrawBattleInventory(PokemonInstType* pokeLeft, PokemonInstType* pokeRight, uint8_t language);
extern uint8_t language;
uint8_t DrawLanguageSelection(void);
#endif
