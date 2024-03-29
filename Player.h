
#ifndef _PLAYERH_
#define _PLAYERH_

#include <stdint.h>
#include <stdbool.h>
#include "StructDec.h"

extern PlayerType p1;
extern ItemInventoryType playerInventory[3];
extern PokemonTeamType pokeTeam;

void InitPlayer(void);
void InitInventory(void);
void InitTeam(void);
void StartTeam(void);
void addPokemon(PokemonInstType* newPokemon, uint32_t index);
void DrinkBoba(void);
void LoseBattle(void);
bool MoveUp(void);
bool MoveDown(void);
bool MoveLeft(void);
bool MoveRight(void);

#endif
