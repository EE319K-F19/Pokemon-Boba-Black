#ifndef _Shop_
#define _Shop_

#include <stdint.h>
#include "Player.h"
// #include "ImagesOther.h"
#include "Draw.h"

// typedef struct Shop ShopType;
typedef struct Item ItemType;
typedef struct ItemInventory ItemInventoryType;
typedef struct itemInst ItemInstType;

struct Item {
	char* name;
	SpriteType sprite;
	uint32_t price;
	char* price_string;
	uint32_t index;
};

struct ItemInventory {
	ItemType item;
	uint32_t count;
};


struct itemInst {
	uint16_t xPos;
	uint16_t yPos;
	ItemType item;
};

	
void Shop_Init(void);
// void makePurchase(PlayerType* player, ItemType item);
void DrawShopScreen(SpriteSelectType itemSprites, const ItemInstType shopItems[3]);

#endif
