
#ifndef _PLAYERH_
#define _PLAYERH_

#include <stdint.h>
#include <stdbool.h>
#include "StructDec.h"

extern PlayerType p1;
extern ItemInventoryType playerInventory[3];
extern PokemonInstType* playerTeam;

void InitPlayer(void);
void InitInventory(void);
void InitTeam(PokemonInstType* starterTeam);
void DrinkBoba(void);
void LoseBattle(void);
bool MoveUp(void);
bool MoveDown(void);
bool MoveLeft(void);
bool MoveRight(void);

#endif
