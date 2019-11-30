
#include <stdint.h>
#include "ST7735.h"
#include "Random.h"

#include "ADC_Joystick.h"
#include "Battle.h"

#include "Draw.h"
#include "DrawScreen.h"
#include "Field.h"
#include "ImagesPokemon2.h"
#include "Player.h"
#include "PokemonType.h"
#include "SystemInfo.h"
#include "TextSprites.h"
#include "Shop.h"

ItemInstType shopItems[3];
SpriteInstType itemInsts[3];

PokemonType NullT;
PokemonType BulbasaurT;
PokemonType SquirtleT;
PokemonType CharmanderT;
PokemonType PidgeyT;
PokemonType PikachuT;

PokemonType starters[3];
SpriteInstType starterInsts[3];

void InitPokemon(){
	//uint16_t nullSprite[1] = {0x0000};
	//SpriteType nullS = {nullSprite, 1, 1};
	SpriteType bulbasaurS = {bulbasaur, 40, 40};
	SpriteType squirtleS = {squirtle, 40, 40};
	SpriteType charmanderS = {charmander, 40, 40};
	SpriteType pidgeyS = {pidgey, 40, 40};
	SpriteType pikachuS = {pikachu, 40, 40};
	
	//NullT = (PokemonType) {"Null", Grass, nullS, 0, 0, 0, 0, 0, 0};
	BulbasaurT = (PokemonType) {"Bulbasaur", Grass, bulbasaurS, 45, 49, 49, 65, 65, 45, 0};
	SquirtleT = (PokemonType) {"Squirtle", Water, squirtleS, 44, 48, 65, 50, 64, 43, 1};
	CharmanderT = (PokemonType) {"Charmander", Fire, charmanderS, 39, 52, 43, 60, 50, 65, 2};
	PidgeyT = (PokemonType) {"Pidgey", Flying, pidgeyS, 40, 45, 40, 35, 35, 56, 3};
	PikachuT = (PokemonType) {"Pikachu", Electric, pikachuS, 35, 55, 40, 50, 50, 90, 4};
	
	starters[0] = BulbasaurT;
	starters[1] = SquirtleT;
	starters[2] = CharmanderT;
	
	PokemonInstType BulbasaurStart = {2, 130, BulbasaurT.mhealth, BulbasaurT};
	PokemonInstType SquirtleStart = {44, 130, SquirtleT.mhealth, SquirtleT};
	PokemonInstType CharmanderStart = {86, 130, CharmanderT.mhealth, CharmanderT};
	
	starterInsts[0] = (SpriteInstType) {BulbasaurStart.xPos, BulbasaurStart.yPos, BulbasaurStart.species.sprite};
	starterInsts[1] = (SpriteInstType) {SquirtleStart.xPos, SquirtleStart.yPos, SquirtleStart.species.sprite};
	starterInsts[2] = (SpriteInstType) {CharmanderStart.xPos, CharmanderStart.yPos, CharmanderStart.species.sprite};
}

uint8_t DrawLanguageSelection(void){
	ST7735_FillRect(0, 100, 128, 60, 0xFFFF);
	char *a[2];
	int selected = 0;
	a[0] = "English";
	a[1] = "Espanol";
	ST7735_SetCursor(1, 5);
	ST7735_OutString("Please select a language.");
	for(int i=0; i<2; i++){
			ST7735_SetCursor(3, 12+i);
			ST7735_OutString(a[i]);
	}
	
	while(1){
		while(ADCStatus == 0){}
			
		uint8_t yDir = getJoystickY();
		ADCStatus = 0;
		
		if(yDir == 2 && selected < 1){
			selected++;
		}else if(yDir == 0 && selected > 0){
			selected--;
		}
		
		for(int i=0; i<2; i++){
			ST7735_SetCursor(1, 12+i);
			if(i==selected) ST7735_OutString("*");
			else ST7735_OutString(" ");
		}
		
		if(isPE3Pressed()){
			return selected;
		}
	}
}

PokemonType DrawTitleScreen(uint8_t language){
	SpriteSelectType starterScreen = {starterInsts, 3, 0};
	ST7735_FillScreen(0xFFFF);
	
	DrawAllSprites(starterScreen);
	ST7735_SetTextColor(ST7735_BLACK);
	ST7735_SetCursor(1, 1);
	if(language) ST7735_OutString("Pokemon Boba Negro");
	else ST7735_OutString("Pokemon Boba Black");
	ST7735_SetCursor(1, 2);
	if(language) ST7735_OutString("Hecho por Andy/Iris");
	else ST7735_OutString("Made by Andy & Iris");
	ST7735_SetCursor(1, 3);
	if(language) ST7735_OutString("Seleccione\n su entrante");
	else ST7735_OutString("Please select your\n starter.");
	
	while(1){
		
		while(ADCStatus == 0){}
		
		uint8_t xDir = getJoystickX();
		uint8_t yDir = getJoystickY();
		ADCStatus = 0;
		
		if(xDir == 2){
			starterScreen.currentIndex = (starterScreen.currentIndex + 1)%3;
		}else if(xDir == 0){
			starterScreen.currentIndex = starterScreen.currentIndex - 1;
			if(starterScreen.currentIndex < 0) starterScreen.currentIndex = 2;
		}
			
		DrawSelection(&starterScreen, 0x0000, 0xFFFF, 1);
		if(isPE3Pressed()) return starters[starterScreen.currentIndex];
  }
}

bool DrawWorld(uint8_t language){
	//draws black border around the edges of the screen
	
	PokemonType allPokemon[] = {BulbasaurT, SquirtleT, CharmanderT, PidgeyT, PikachuT};
	uint8_t numPokemon = 5;
	DrawBorder(GAME_BORDER_W, GAME_BORDER_W, _width-2*GAME_BORDER_W, _height-2*GAME_BORDER_W, GAME_BORDER_W, GAME_BORDER_COLOR);
	
	while(1){
		
		if(p1.happiness >= 100){
			return true;
		}else if(p1.happiness <= 0){
			return false;
		}
		
		while(ADCStatus == 0){}
			
		uint8_t xDir = getJoystickX();
		uint8_t yDir = getJoystickY();
		ADCStatus = 0;
		
		bool moved = false;
		if(xDir == 0){
			moved = MoveLeft();
		}else if(xDir == 2){
			moved = MoveRight();
		}else if(yDir == 0){
			moved = MoveUp();
		}else if(yDir == 2){
			moved = MoveDown();
		}
		DrawField();
		uint8_t encounter = Random()%10;
		encounter = 1; //testing map
		if(moved && encounter == 0){
			ST7735_FillScreen(0xFFFF);
			uint8_t pokemonRan = Random()%5;
			PokemonType selected = allPokemon[pokemonRan];
			DrawBattleScreen(&playerTeam[0], &selected, language);
			//Delay100ms(20);
		}
		
		if(isPE2Pressed()){
			ClearScreenGrid();
			ST7735_FillScreen(0xFFFF);
			
			ST7735_SetCursor(3, 5);
			if(language) ST7735_OutString("Monedas: ");
			else ST7735_OutString("Coins: ");
			//uint32_t coinsC = p1.coins;
			if(p1.coins > 999) ST7735_OutChar((char) (p1.coins/1000) + 0x30);
			if(p1.coins > 99) ST7735_OutChar((char) (p1.coins/100) + 0x30);
			if(p1.coins > 9) ST7735_OutChar((char) (p1.coins/10) + 0x30);
			ST7735_OutChar((char) (p1.coins%10) + 0x30);
			ST7735_OutString("C");
			
			ST7735_SetCursor(3, 6);
			if(language) ST7735_OutString("Felicidad: ");
			else ST7735_OutString("Happiness: ");
			if(p1.happiness > 99) ST7735_OutChar((char) (p1.happiness/100) + 0x30);
			if(p1.happiness > 9) ST7735_OutChar((char) (p1.happiness/10) + 0x30);
			ST7735_OutChar((char) (p1.happiness%10) + 0x30);
			ST7735_OutString("/100");
			
			while(1){
				if(isPE2Pressed()) break;
			}
		}else if(isPE3Pressed()){
			if(GetFieldGrid(p1.YPos-1, p1.XPos) == S){
				ClearScreenGrid();
				SpriteSelectType shopScreen = {itemInsts, 3, 0};
				DrawShopScreen(&p1, playerInventory, shopScreen, shopItems, language);
			}
		}
	}
}

void DrawBattleScreen(PokemonInstType* pokeLeft, const PokemonType* pokeRight, uint8_t language){
	ClearScreenGrid();
	ST7735_FillScreen(0xFFFF);
	SpriteInstType leftInst = (SpriteInstType) {2, 90, pokeLeft->species.sprite};
	SpriteInstType rightInst = (SpriteInstType) {86, 90, pokeRight->sprite};
	
	PokemonInstType pokemonRight = {86, 90, pokeRight->mhealth, *pokeRight};
	
	DrawSpriteImg(leftInst);
	DrawSpriteImg(rightInst);
	
	SpriteType fightText;
	if(language) {
		fightText = (SpriteType){lucha, 32, 16};
	}
	else{
		fightText = (SpriteType){fight, 32, 16};
	}
	SpriteInstType fightInst = {14, 120, fightText};
	
	SpriteType pokeText = {pokemon, 32, 16};
	SpriteInstType pokeInst = {14, 150, pokeText};
	
	SpriteType itemText = {item, 32, 16};
	SpriteInstType itemInst = {84, 120, itemText};
	
	SpriteType runText;
	if(language) {
		runText = (SpriteType){correr, 32, 16};
	}
	else{
		runText = (SpriteType){run, 32, 16};
	}
	SpriteInstType runInst = {84, 150, runText};
	
	SpriteInstType battleCommands[4] = {fightInst, itemInst, pokeInst, runInst};
	SpriteSelectType battleScreen = {battleCommands, 4, 0};
	DrawAllSprites(battleScreen);
	
	ST7735_FillRect(pokeLeft->xPos+5, 45, 30, 2, 0x0000);
	ST7735_FillRect(pokemonRight.xPos+5, 45, 30, 2, 0x0000);
	
	ST7735_FillRect(pokeLeft->xPos+5, 45, pokeLeft->chealth*30/pokeLeft->species.mhealth, 2, 0x00FF);
	ST7735_FillRect(pokemonRight.xPos+5, 45, pokemonRight.chealth*30/pokemonRight.species.mhealth, 2, 0x00FF);
	
	while(1){
		
		while(ADCStatus == 0){}
			
		uint8_t xDir = getJoystickX();
		uint8_t yDir = getJoystickY();
		ADCStatus = 0;
		
		if(xDir == 2){
			if(battleScreen.currentIndex == 0 || battleScreen.currentIndex == 2) battleScreen.currentIndex = battleScreen.currentIndex + 1;
		}else if(xDir == 0){
			if(battleScreen.currentIndex == 1 || battleScreen.currentIndex == 3) battleScreen.currentIndex = battleScreen.currentIndex - 1;
		}else if(yDir == 2){
			if(battleScreen.currentIndex == 0 || battleScreen.currentIndex == 1) battleScreen.currentIndex = battleScreen.currentIndex + 2;
		}else if(yDir == 0){
			if(battleScreen.currentIndex == 2 || battleScreen.currentIndex == 3) battleScreen.currentIndex = battleScreen.currentIndex - 2;
		}
		
		DrawSelection(&battleScreen, 0x0000, 0xFFFF, 1);
		if(isPE3Pressed()){
			if(battleScreen.currentIndex == 3){
				break;
			}else if(battleScreen.currentIndex == 1){
				DrawBattleInventory(pokeLeft, &pokemonRight, language);
				DrawAllSprites(battleScreen);
			}else if(battleScreen.currentIndex == 0){
				int results = DrawMoveCommands(pokeLeft, &pokemonRight, language);
				if(results == 0) DrawAllSprites(battleScreen);
				else{
					if(results == 1){
						ST7735_SetCursor(1, 12);
						if(language) ST7735_OutString("Salvaje ");
						else ST7735_OutString("Wild ");
						ST7735_OutString(pokeRight->name);
						if(language) ST7735_OutString("\n desmayado.");
						else ST7735_OutString("\n fainted.");
						while(1) if(isPE3Pressed()) break;
						ST7735_FillRect(0, 94, 128, 56, 0xFFFF);
						
						uint8_t coinsGained = Random()%15 + 20;
						p1.coins += coinsGained;
						ST7735_SetCursor(1, 12);
						if(language) ST7735_OutString("Ganaste ");
						else ST7735_OutString("You gained ");
						ST7735_OutChar((char) (coinsGained/10)+0x30);
						ST7735_OutChar((char) (coinsGained%10)+0x30);
						ST7735_OutString("C.");
						while(1) if(isPE3Pressed()) break;
						
						
						break;
					}else {
						ST7735_SetCursor(1, 12);
						if(language) ST7735_OutString("Tu ");
						else ST7735_OutString("Your ");
						ST7735_OutString(pokeLeft->species.name);
						if(language) ST7735_OutString("\n desmayado.");
						else ST7735_OutString("\n fainted.");
						pokeLeft->chealth = 1;
						while(1) if(isPE3Pressed()) break;
						ST7735_SetCursor(1, 12);
						if(language) ST7735_OutString("Tu felicidad\n cayó por 10.");
						else ST7735_OutString("Your happiness\n dropped by 10.");
						uint8_t drop = 10;
						if(p1.happiness < 10) drop = p1.happiness;
						p1.happiness -= drop;
						while(1) if(isPE3Pressed()) break;
						break;
					}
				}
			}
		}
  }
}

void DrawBattleInventory(PokemonInstType* pokeLeft, PokemonInstType* pokeRight, uint8_t language){
	ST7735_FillRect(0, 100, 128, 60, 0xFFFF);
	char *a[4];
	int selected = 0;
	for(int i=0; i<3; i++){
		a[i] = shopItems[i].item.name[language];
	}
	if(language) a[3] = "espalda";
	a[3] = "back";
	
	for(int i=0; i<4; i++){
			ST7735_SetCursor(3, 12+i);
			ST7735_OutString(a[i]);
			if(i!=3) ST7735_OutString(" x");
			if(i!=3) ST7735_OutChar((char) (playerInventory[i].count + 0x30));
	}
	while(1){
		while(ADCStatus == 0){}
			
		uint8_t yDir = getJoystickY();
		ADCStatus = 0;
		
		if(yDir == 2 && selected < 3){
			selected++;
		}else if(yDir == 0 && selected > 0){
			selected--;
		}
		
		for(int i=0; i<4; i++){
			ST7735_SetCursor(1, 12+i);
			if(i==selected) ST7735_OutString("*");
			else ST7735_OutString(" ");
		}
		
		if(isPE3Pressed()){
			if(selected == 3){
				ST7735_FillRect(0, 100, 128, 60, 0xFFFF);
				break;
			}else {
				ST7735_SetCursor(1, 12);
				ST7735_FillRect(0, 100, 128, 60, 0xFFFF);
				if(playerInventory[selected].count > 0){
					if(language) ST7735_OutString("Usaste un\n ");
					else ST7735_OutString("You used a\n ");
					ST7735_OutString(a[selected]);
					playerInventory[selected].count --;
					while(1){if(isPE3Pressed()) break;};
					
					if(selected == 1){
						ST7735_SetCursor(1, 12);
						ST7735_FillRect(0, 100, 128, 60, 0xFFFF);
						ST7735_OutString(pokeLeft->species.name);
						if(language) ST7735_OutString("ha sido \n curado");
						else ST7735_OutString(" has been \n healed.");
						pokeLeft->chealth = pokeLeft->species.mhealth;
						ST7735_FillRect(pokeLeft->xPos+5, 45, 30, 2, 0x0000);
						ST7735_FillRect(pokeLeft->xPos+5, 45, pokeLeft->chealth*30/pokeLeft->species.mhealth, 2, 0x00FF);
						while(1){if(isPE3Pressed()) break;};
					}else if(selected == 2){
						ST7735_SetCursor(1, 12);
						ST7735_FillRect(0, 100, 128, 60, 0xFFFF);
						if(language) ST7735_OutString("¡Tu felicidad\n aumentó en 25!");
						else ST7735_OutString("Your happiness\n increased by 25!");
						p1.happiness += 25;
						if(p1.happiness > 100) p1.happiness = 100;
						while(1){if(isPE3Pressed()) break;};
					}
				}else {
					if(language) ST7735_OutString("No tienes ninguno\n ");
					else ST7735_OutString("You don't have any\n ");
					ST7735_OutString(a[selected]);
					while(1){if(isPE3Pressed()) break;};
				}
				ST7735_FillRect(0, 100, 128, 60, 0xFFFF);
				for(int i=0; i<4; i++){
					ST7735_SetCursor(3, 12+i);
					ST7735_OutString(a[i]);
					if(i!=3) ST7735_OutString(" x");
					if(i!=3) ST7735_OutChar((char) (playerInventory[i].count + 0x30));
				}
			}
		}
	}
}

uint8_t DrawMoveCommands(PokemonInstType* pokeLeft, PokemonInstType* pokeRight, uint8_t language){
	
	ST7735_FillRect(10, 104, 106, 46, 0xFFFF);
	MoveType normal = NormalMoves[pokeLeft->species.moveSet];
	MoveType signature = SignatureMoves[pokeLeft->species.moveSet];
	uint8_t selected = 0;
	char *a[3];
	a[0] = normal.name[language];
	a[1] = signature.name[language];
	if(language) a[2] = "espalda";
	else a[2] = "back";
	
	for(int i=0; i<3; i++){
			ST7735_SetCursor(3, 12+i);
			ST7735_OutString(a[i]);
	}
	while(1){
		while(ADCStatus == 0){}
			
		uint8_t yDir = getJoystickY();
		ADCStatus = 0;
		
		if(yDir == 2 && selected < 2){
			selected++;
		}else if(yDir == 0 && selected > 0){
			selected--;
		}
		
		for(int i=0; i<3; i++){
			ST7735_SetCursor(1, 12+i);
			if(i==selected) ST7735_OutString("*");
			else ST7735_OutString(" ");
		}
		
		if(isPE3Pressed()){
			MoveType selectedMove;
			if(selected == 0){
				selectedMove = normal;
			}else if(selected == 1){
				selectedMove = signature;
			}else{
				ST7735_FillRect(0, 104, 116, 46, 0xFFFF);
				return 0;
			}
			ST7735_FillRect(0, 104, 116, 46, 0xFFFF);
			ST7735_SetCursor(1, 12);
			ST7735_OutString(pokeLeft->species.name);
			if(language) ST7735_OutString(" usado \n ");
			else ST7735_OutString(" used \n ");
			ST7735_OutString(selectedMove.name[language]);
			while(1) {if(isPE3Pressed()) break;}
			
			ST7735_FillRect(0, 104, 116, 46, 0xFFFF);
			uint8_t effectiveness = TypesArray[selectedMove.type][pokeRight->species.type];
			ST7735_SetCursor(1, 12);
			if(effectiveness == A){
				if(language) ST7735_OutString("Muy efectivo!");
				else ST7735_OutString("Very effective!");
			}else if(effectiveness == C){
				if(language) ST7735_OutString("Poco efectivo.");
				else ST7735_OutString("Not very effective.");
			}else if(effectiveness == D){
				if(language) ST7735_OutString("Sin efecto...");
				else ST7735_OutString("No effect...");
			}
			uint8_t attack;
			uint8_t defense;
			if(selectedMove.category == CAT_PHYSICAL){
				attack = pokeLeft->species.attack;
				defense = pokeRight->species.defense;
			}else {
				attack = pokeLeft->species.spattack;
				defense = pokeRight->species.spdefense;
			}
			
			uint8_t randomDamMul = Random()%25;
			uint32_t damage = ((8*attack*selectedMove.power/defense)/20 + 2)*(effectiveness*(75+randomDamMul))/2/100 + 1;
			if(damage > pokeRight->chealth) damage = pokeRight->chealth;
			pokeRight->chealth = pokeRight->chealth - damage;
			
			ST7735_FillRect(pokeRight->xPos+5, 45, 30, 2, 0x0000);
			ST7735_FillRect(pokeRight->xPos+5, 45, pokeRight->chealth*30/pokeRight->species.mhealth, 2, 0x00FF);
			
			while(1) {if(isPE3Pressed()) break;}
			
			if(pokeRight->chealth == 0) {
				ST7735_FillRect(0, 94, 128, 56, 0xFFFF);
				return 1;
			}
			
			bool useNormal = Random()%2 == 0;
			if(useNormal){
				selectedMove = NormalMoves[pokeRight->species.moveSet];
			}else {
				selectedMove = SignatureMoves[pokeRight->species.moveSet];
			}
			
			ST7735_FillRect(0, 104, 116, 46, 0xFFFF);
			ST7735_SetCursor(1, 12);
			ST7735_OutString(pokeRight->species.name);
			if(language) ST7735_OutString(" usado \n ");
			else ST7735_OutString(" used \n ");
			ST7735_OutString(selectedMove.name[language]);
			while(1) {if(isPE3Pressed()) break;}
			
			bool effectiveText = true;
			ST7735_FillRect(0, 104, 116, 46, 0xFFFF);
			effectiveness = TypesArray[selectedMove.type][pokeLeft->species.type];
			ST7735_SetCursor(1, 12);
			if(effectiveness == A){
				if(language) ST7735_OutString("Muy efectivo!");
				else ST7735_OutString("Very effective!");
			}else if(effectiveness == C){
				if(language) ST7735_OutString("Poco efectivo.");
				else ST7735_OutString("Not very effective.");
			}else if(effectiveness == D){
				if(language) ST7735_OutString("Sin efecto...");
				else ST7735_OutString("No effect...");
			}else{
				effectiveText = false;
			}
			
			if(selectedMove.category == CAT_PHYSICAL){
				attack = pokeRight->species.attack;
				defense = pokeLeft->species.defense;
			}else {
				attack = pokeRight->species.spattack;
				defense = pokeLeft->species.spdefense;
			}
			
			randomDamMul = Random()%25;
			damage = ((8*attack*selectedMove.power/defense)/20 + 2)*(effectiveness*(75+randomDamMul))/2/100 + 1;
			if(damage > pokeLeft->chealth) damage = pokeLeft->chealth;
			pokeLeft->chealth = pokeLeft->chealth - damage;
			
			ST7735_FillRect(pokeLeft->xPos+5, 45, 30, 2, 0x0000);
			ST7735_FillRect(pokeLeft->xPos+5, 45, pokeLeft->chealth*30/pokeLeft->species.mhealth, 2, 0x00FF);
			
			while(1) if(isPE3Pressed()) break;
			
			if(pokeLeft->chealth == 0) {
				ST7735_FillRect(0, 94, 128, 56, 0xFFFF);
				return 2;
			}
			ST7735_FillRect(0, 94, 128, 56, 0xFFFF);
			return 0;
		}
	}
}
