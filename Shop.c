
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

ItemType bobaItem;
ItemType potionItem;
ItemType pokeballItem;

void InitShop(void){
	
	SpriteType bobaSprite = {boba, 40, 40};
	SpriteType potionSprite = {healthPotion, 40, 40};
	SpriteType pokeballSprite = {pokeball, 40, 40};
	
	ItemType bobaItem = {{"boba", "boba"}, bobaSprite, 70, "70 C", 2};
	ItemType potionItem = {{"health potion", "poción de salud"}, potionSprite, 20, "20 C", 1};
	ItemType pokeballItem = {{"pokeball", "pokeball"}, pokeballSprite, 10, "10 C", 0};
	
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

void DrawShopScreen(PlayerType* p1, ItemInventoryType* inventory, SpriteSelectType shopScreen, const ItemInstType shopItems[3], uint8_t language){
	ST7735_FillScreen(0xFFFF);
	
	DrawAllSprites(shopScreen);
	ST7735_SetTextColor(ST7735_BLACK);
	ST7735_SetCursor(1, 2);
	if(language) ST7735_OutString("Tienda de Pokeboba");
	else ST7735_OutString("Pokeboba Shop");
	ST7735_SetCursor(1, 3);
	if(language) ST7735_OutString("¿Que le gustaria");
	else ST7735_OutString("What would you like");
	ST7735_SetCursor(1, 4);
	if (language) ST7735_OutString("comprar?");
	else ST7735_OutString("to buy?");
	
	ST7735_SetCursor(2, 13);
	ST7735_OutString(shopItems[0].item.price_string);
	ST7735_SetCursor(9, 13);
	ST7735_OutString(shopItems[1].item.price_string);
	ST7735_SetCursor(16, 13);
	ST7735_OutString(shopItems[2].item.price_string);
	
	ST7735_SetCursor(1, 14);
	ST7735_OutString(shopItems[shopScreen.currentIndex].item.name[language]);
	if(language) ST7735_OutString("\n (Tener: ");
	else ST7735_OutString("\n (Have: ");
	ST7735_OutChar((char) (inventory[shopScreen.currentIndex].count + 0x30));
	ST7735_OutString(")");
	
	while(1){
		
		ST7735_SetCursor(1, 5);
		if(language) ST7735_OutString("Tienes: ");
		else ST7735_OutString("You have: ");
		if(p1->coins > 999) ST7735_OutChar((char) (p1->coins/1000) + 0x30);
		if(p1->coins > 99) ST7735_OutChar((char) (p1->coins/100) + 0x30);
		if(p1->coins > 9) ST7735_OutChar((char) (p1->coins/10) + 0x30);
		ST7735_OutChar((char) (p1->coins%10) + 0x30);
		ST7735_OutString("C  ");
		while(ADCStatus == 0){}
		uint8_t xDir = getJoystickX();
		uint8_t yDir = getJoystickY();
		ADCStatus = 0;
		
		if(xDir == 0 || xDir == 2){
			if(xDir == 2){
				shopScreen.currentIndex = (shopScreen.currentIndex + 1)%3;
			}else if(xDir == 0){
				shopScreen.currentIndex = shopScreen.currentIndex - 1;
				if(shopScreen.currentIndex < 0) shopScreen.currentIndex = 2;
			}
			ST7735_FillRect(0, 140, 128, 20, 0xFFFF);
			ST7735_SetCursor(1, 14);
			ST7735_OutString(shopItems[shopScreen.currentIndex].item.name[language]);
			if(language) ST7735_OutString("\n (Tener: ");
		  else ST7735_OutString("\n (Have: ");
			ST7735_OutChar((char) (inventory[shopScreen.currentIndex].count + 0x30));
			ST7735_OutString(")");
		}
			
		DrawSelection(&shopScreen, 0x0000, 0xFFFF, 1);
		if(isPE2Pressed()) break;
		else if(isPE3Pressed()){
			if(p1->coins >= shopItems[shopScreen.currentIndex].item.price){
				p1->coins -= shopItems[shopScreen.currentIndex].item.price;
				ST7735_SetCursor(1, 14);
				if(language) ST7735_OutString("Compraste un\n ");
				else ST7735_OutString("You purchased a\n ");
				ST7735_OutString(shopItems[shopScreen.currentIndex].item.name[language]);
				inventory[shopScreen.currentIndex].count ++;
			}else {
				ST7735_SetCursor(1, 14);
				if(language) ST7735_OutString("¡Uy! No tienes\n suficientes monedas");
				else ST7735_OutString("Oops! You don't\n have enough coins");
			}
		}
  }
}

