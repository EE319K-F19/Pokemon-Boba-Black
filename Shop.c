
#include "Player.h"
// #include "ImagesOther.h"
#include "Draw.h"
#include <stdlib.h>
#include <stdint.h>
#include "ADC_Joystick.h"

//const SpriteType HealthPotion = {healthPotion, 40, 40};
//const SpriteType Pokeball = {pokeball, 40, 40};
	

//void makePurchase(PlayerType* player, ItemType item){
//	if(player->coins < item.price){
//		// throw error that says you are too broke to buy
//		return;
//	}
//	player->coins -= item.price;
//	player->playerInventory[item.index].count++;
//}

	/// SHOP STUFF
//	SpriteType bobaSprite = {boba, 40, 40};
//	SpriteType potionSprite = {healthPotion, 40, 40};
//	SpriteType pokeballSprite = {pokeball, 40, 40};
//	
//	ItemType bobaItem = {"boba", bobaSprite, 60, "60 C", 2};
//	ItemType potionItem = {"health potion", potionSprite, 30, "30 C", 1};
//	ItemType pokeballItem = {"pokeball", pokeballSprite, 20, "20 C", 0};
//	
//	ItemInstType bobaShop = {86, 80, bobaItem};
//	ItemInstType potionShop = {44, 80, potionItem};
//	ItemInstType pokeballShop = {2, 80, pokeballItem};
//	
//	const ItemInstType shopItems[] = {pokeballShop, potionShop, bobaShop};
//	
//	const SpriteInstType itemInsts[3] = {
//		(SpriteInstType) {pokeballShop.xPos, pokeballShop.yPos+pokeballShop.item.sprite.height-1, pokeballShop.item.sprite},
//		(SpriteInstType) {potionShop.xPos, potionShop.yPos+potionShop.item.sprite.height-1, potionShop.item.sprite},
//		(SpriteInstType) {bobaShop.xPos, bobaShop.yPos+bobaShop.item.sprite.height-1, bobaShop.item.sprite}
//	};
//	SpriteSelectType shopScreen = {itemInsts, 3, 0};
	// DrawShopScreen(shopScreen, shopItems);
	
	// END OF SHOP STUFF

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
		Delay100ms(2);
  }
}

