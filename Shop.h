#ifndef _Shop_
#define _Shop_

#include <stdint.h>
#include "Player.h"
#include "ImagesOther.h"
#include "Draw.h"

typedef struct Shop ShopType;

struct Shop {
	PlayerType* player;
	ItemType shopItems[3];
//itemSprites = s

};

	
void Shop_Init();
void makePurchase(PlayerType* player, ItemType item);
void displayShop(SpriteSelectType* itemSprites);

#endif