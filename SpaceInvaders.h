
#ifndef _SPACEINVADERSH_
#define _SPACEINVADERSH_

#include "StructDec.h"

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
void InitPlayer(void);
void InitPokemon(void);
PokemonType DrawTitleScreen(SpriteSelectType starterScreen);
void DrawBattleScreen(const PokemonInstType* pokeLeft, PokemonType* pokeRight);
void DrawWorld(PlayerType p1, FieldType mainField);


#endif
