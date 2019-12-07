
#ifndef _DRAWSCREENH_
#define _DRAWSCREENH_

#include <stdbool.h>
#include <stdint.h>
#include "StructDec.h"

extern uint8_t language;
uint8_t DrawLanguageSelection(void);
PokemonType DrawTitleScreen(uint8_t language);
bool DrawWorld(uint8_t language);
void DrawStatusScreen(uint8_t language);
void DrawBattleScreen(PokemonInstType* pokeLeft, PokemonInstType* pokeRight, uint8_t language);
PokemonInstType* DrawPokemonInventory(uint8_t language);
void DrawSwapPokemon(uint8_t language, PokemonInstType* pokeRight);
bool PokemonAllDead(void);
void RestoreDeadPokemon(void);
uint8_t DrawMoveCommands(PokemonInstType* pokeLeft, PokemonInstType* pokeRight, uint8_t language);
uint8_t DrawBattleInventory(PokemonInstType* pokeLeft, PokemonInstType* pokeRight, uint8_t language);
int8_t DrawSimpleMenu(char *menuItems[], uint8_t menuLength, bool useBack);
void DrawHPBars(PokemonInstType* pokeLeft, PokemonInstType* pokeRight);

extern PokemonType allPokemon[20];
extern uint32_t numPokemonSpecies;
void InitPokemon(void);
PokemonInstType GenerateRandomPokemonInit(uint8_t index);
PokemonInstType GenerateRandomPokemon(uint8_t index);
void MoveWorldPokemon(void);

#endif
