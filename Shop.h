#ifndef _Shop_
#define _Shop_

#include <stdint.h>
#include "StructDec.h"

extern ItemInstType shopItems[3];
extern SpriteInstType itemInsts[3];

extern ItemType bobaItem;
extern ItemType potionItem;
extern ItemType pokeballItem;

void Shop_Init(void);
// void makePurchase(PlayerType* player, ItemType item);
void DrawShopScreen(PlayerType* p1, ItemInventoryType* inventory, SpriteSelectType itemSprites, const ItemInstType shopItems[3]);

#endif
