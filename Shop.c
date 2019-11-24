
#include "Player.h"
#include "ImagesOther.h"
#include "Draw.h"
#include <stdlib.h>
#include <stdint.h>

const SpriteType HealthPotion = {healthPotion, 16, 16};
const SpriteType Pokeball = {pokeball, 16, 16};
	

void makePurchase(PlayerType* player, ItemType item){
	if(player->coins < item.price){
		// throw error that says you are too broke to buy
		return;
	}
	player->coins -= item.price;
	player->playerInventory[item.index].count++;
}

void displayShop(SpriteSelectType* itemSelect){
	// display Sprite selection menu
	
	for(int i=0; i<3; i++){
		if(i == itemSelect->currentIndex){
			DrawSpriteSelectionDefault(itemSelect->sprites[i]);
		}else {
			DrawSpriteImg(itemSelect->sprites[i]);
		}
	}
	nextIndex(itemSelect);
	Delay10ms(10); 
}