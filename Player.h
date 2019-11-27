
#ifndef _PLAYERH_
#define _PLAYERH_

#include <stdint.h>
#include <stdbool.h>
#include "StructDec.h"

void DrawSpriteImgPlayer(PlayerType player);

bool MoveUp(PlayerType *player);
bool MoveDown(PlayerType *player);
bool MoveLeft(PlayerType *player);
bool MoveRight(PlayerType *player);

#endif
