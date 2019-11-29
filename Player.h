
#ifndef _PLAYERH_
#define _PLAYERH_

#include <stdint.h>
#include <stdbool.h>
#include "StructDec.h"

extern PlayerType p1;

void DrawSpriteImgPlayer(PlayerType player);

void InitPlayer(void);
bool MoveUp(PlayerType *player);
bool MoveDown(PlayerType *player);
bool MoveLeft(PlayerType *player);
bool MoveRight(PlayerType *player);

#endif
