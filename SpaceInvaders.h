
#ifndef _SPACEINVADERSH_
#define _SPACEINVADERSH_

#include "StructDec.h"

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
void InitPlayer(void);
void InitPokemon(void);
PokemonType DrawTitleScreen(SpriteSelectType starterScreen);
void DrawBattleScreen(PokemonInstType* pokeLeft, const PokemonType* pokeRight);
void DrawWorld(PlayerType p1);
uint8_t DrawMoveCommands(PokemonInstType* pokeLeft, PokemonInstType* pokeRight);

#endif
