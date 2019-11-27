
#ifndef _DRAWSCREENH_
#define _DRAWSCREENH_

#include <stdint.h>
#include "StructDec.h"

extern PokemonType NullT;
extern PokemonType BulbasaurT;
extern PokemonType SquirtleT;
extern PokemonType CharmanderT;
extern PokemonType PidgeyT;
extern PokemonType PikachuT;

extern PokemonType starters[3];
extern SpriteInstType starterInsts[3];

void InitPokemon(void);
PokemonType DrawTitleScreen(SpriteSelectType starterScreen);
void DrawBattleScreen(const PokemonInstType* pokeLeft, PokemonType* pokeRight);
void DrawWorld(PlayerType p1, FieldType mainField);

#endif