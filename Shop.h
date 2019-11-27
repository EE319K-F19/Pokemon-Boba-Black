#ifndef _Shop_
#define _Shop_

#include <stdint.h>
#include "StructDec.h"

extern ItemInstType shopItems[3];
extern SpriteInstType itemInsts[3];

void Shop_Init(void);
// void makePurchase(PlayerType* player, ItemType item);
void DrawShopScreen(PlayerType* p1, SpriteSelectType itemSprites, const ItemInstType shopItems[3]);

#endif
