
#include <stdint.h>
#include <stdlib.h>
#include "ADC_Joystick.h"
#include "Draw.h"
#include "ImagesOther.h"
#include "Shop.h"
#include "StructDec.h"

//void makePurchase(PlayerType* player, ItemType item){
//	if(player->coins < item.price){
//		// throw error that says you are too broke to buy
//		return;
//	}
//	player->coins -= item.price;
//	player->playerInventory[item.index].count++;
//}

void Shop_Init(void){
	
	SpriteType bobaSprite = {boba, 40, 40};
	SpriteType potionSprite = {healthPotion, 40, 40};
	SpriteType pokeballSprite = {pokeball, 40, 40};
	
	ItemType bobaItem = {"boba", bobaSprite, 60, "60 C", 2};
	ItemType potionItem = {"health potion", potionSprite, 30, "30 C", 1};
	ItemType pokeballItem = {"pokeball", pokeballSprite, 20, "20 C", 0};
	
	ItemInstType bobaShop = {86, 80, bobaItem};
	ItemInstType potionShop = {44, 80, potionItem};
	ItemInstType pokeballShop = {2, 80, pokeballItem};
	
	shopItems[0] = pokeballShop;
	shopItems[1] = potionShop;
	shopItems[2] = bobaShop;
	
	SpriteInstType pokeballInst = (SpriteInstType) {pokeballShop.xPos, pokeballShop.yPos+pokeballShop.item.sprite.height-1, pokeballShop.item.sprite};
	SpriteInstType potionInst = (SpriteInstType) {potionShop.xPos, potionShop.yPos+potionShop.item.sprite.height-1, potionShop.item.sprite};
	SpriteInstType bobaInst = (SpriteInstType) {bobaShop.xPos, bobaShop.yPos+bobaShop.item.sprite.height-1, bobaShop.item.sprite};

	itemInsts[0] = pokeballInst;
	itemInsts[1] = potionInst;
	itemInsts[2] = bobaInst;
	
}

void DrawShopScreen(SpriteSelectType shopScreen, const ItemInstType shopItems[3]){
	ST7735_FillScreen(0xFFFF);
	
	DrawAllSprites(shopScreen);
	ST7735_SetTextColor(ST7735_BLACK);
	ST7735_SetCursor(1, 2);
	ST7735_OutString("Pokeboba Shop");
	ST7735_SetCursor(1, 3);
	ST7735_OutString("What would you like");
	ST7735_SetCursor(1, 4);
	ST7735_OutString("to buy?");
	
	ST7735_SetCursor(2, 13);
	ST7735_OutString(shopItems[0].item.price_string);
	ST7735_SetCursor(9, 13);
	ST7735_OutString(shopItems[1].item.price_string);
	ST7735_SetCursor(16, 13);
	ST7735_OutString(shopItems[2].item.price_string);
	
	while(1){
		while(ADCStatus == 0){}
		uint8_t xDir = getJoystickX();
		uint8_t yDir = getJoystickY();
		ADCStatus = 0;
		
		if(xDir == 2){
			shopScreen.currentIndex = (shopScreen.currentIndex + 1)%3;
		}else if(xDir == 0){
			shopScreen.currentIndex = shopScreen.currentIndex - 1;
			if(shopScreen.currentIndex < 0) shopScreen.currentIndex = 2;
		}
			
		DrawSelection(&shopScreen, 0x0000, 0xFFFF, 1);
  }
}

