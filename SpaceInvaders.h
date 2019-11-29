
#ifndef _SPACEINVADERSH_
#define _SPACEINVADERSH_

#include "StructDec.h"
#include <stdbool.h>

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
void InitPlayer(void);
void InitPokemon(void);
PokemonType DrawTitleScreen(SpriteSelectType starterScreen);
void DrawBattleScreen(PlayerType* p1, PokemonInstType* pokeLeft, const PokemonType* pokeRight);
bool DrawWorld(PlayerType p1);
uint8_t DrawMoveCommands(PokemonInstType* pokeLeft, PokemonInstType* pokeRight);
void InitInventory(void);
void DrawBattleInventory(PlayerType *p1, PokemonInstType* pokeLeft, PokemonInstType* pokeRight);

#endif
