
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
#include "Timer1.h"
#include "Sound.h"
#include "../inc/tm4c123gh6pm.h"
#include "ImagesPokemonWorld.h"
#include "ImagesOther.h"

ItemInstType shopItems[3];
SpriteInstType itemInsts[3];

PokemonType BulbasaurT;
PokemonType SquirtleT;
PokemonType CharmanderT;
PokemonType PidgeyT;
PokemonType PikachuT;
PokemonType PsyduckT;
PokemonType PonytaT;
PokemonType DratiniT;
PokemonType EeveeT;
PokemonType JigglypuffT;
PokemonType VulpixT;
PokemonType HorseaT;
PokemonType ButterfreeT;
PokemonType CuboneT;
PokemonType MeowthT;
PokemonType NidoranT;
PokemonType AbraT;
PokemonType GhastlyT;
PokemonType MachampT;
PokemonType GeodudeT;

uint8_t simpleMenuY = 90;
uint16_t simpleMenuColor = 0xFFFF;
uint32_t numPokemonSpecies = 20;
PokemonType allPokemon[20];

int8_t backReturn = -1;
bool seedTimer = true;
uint32_t randomSeed = 1;

void InitPokemon(){
	SpriteType bulbasaurS = {bulbasaur, 40, 40};
	SpriteType squirtleS = {squirtle, 40, 40};
	SpriteType charmanderS = {charmander, 40, 40};
	SpriteType pidgeyS = {pidgey, 40, 40};
	SpriteType pikachuS = {pikachu, 40, 40};
	SpriteType psyduckS = {psyduck, 40, 40};
	SpriteType ponytaS = {ponyta, 40, 40};
	SpriteType dratiniS = {dratini, 40, 40};
	SpriteType jigglypuffS = {jigglypuff, 40, 40};
	SpriteType vulpixS = {vulpix, 40, 40};
	SpriteType eeveeS = {eevee, 40, 40};
	SpriteType horseaS = {horsea, 40, 40};
	SpriteType cuboneS = {cubone, 40, 40};
	SpriteType meowthS = {meowth, 40, 40};
	SpriteType butterfreeS = {butterfree, 40, 40};
	SpriteType nidoranS = {nidoran, 40, 40};
	SpriteType abraS = {abra, 40, 40};
	SpriteType ghastlyS = {ghastly, 40, 40};
	SpriteType machampS = {machamp, 40, 40};
	SpriteType geodudeS = {geodude, 40, 40};

	SpriteType bulbasaurW = {bulbasaurWorldFront, 16, 16};
	SpriteType squirtleW = {squirtleWorldFront, 16, 16};
	SpriteType charmanderW = {charmanderWorldFront, 16, 16};
	SpriteType pidgeyW = {pidgeyWorldFront, 16, 16};
	SpriteType pikachuW = {pikachuWorldFront, 16, 16};
	SpriteType psyduckW = {psyduckWorldFront, 16, 16};
	SpriteType ponytaW = {ponytaWorldFront, 16, 16};
	SpriteType dratiniW = {dratiniWorldFront, 16, 16};
	SpriteType jigglypuffW = {jigglypuffWorldFront, 16, 16};
	SpriteType vulpixW = {vulpixWorldFront, 16, 16};
	SpriteType eeveeW = {eeveeWorldFront, 16, 16};
	SpriteType horseaW = {horseaWorldFront, 16, 16};
	SpriteType cuboneW = {cuboneWorldFront, 16, 16};
	SpriteType meowthW = {meowthWorldFront, 16, 16};
	SpriteType butterfreeW = {butterfreeWorldFront, 16, 16};
	SpriteType nidoranW = {nidoranWorldFront, 16, 16};
	SpriteType abraW = {abraWorldFront, 16, 16};
	SpriteType ghastlyW = {ghastlyWorldFront, 16, 16};
	SpriteType machampW = {machampWorldFront, 16, 16};
	SpriteType geodudeW = {geodudeWorldFront, 16, 16};
	
	BulbasaurT = (PokemonType) {"Bulbasaur", Grass, bulbasaurS, bulbasaurW, 45, 49, 49, 65, 65, 45, 0, grassTile, 3};
	SquirtleT = (PokemonType) {"Squirtle", Water, squirtleS, squirtleW, 44, 48, 65, 50, 64, 43, 1, waterTile, 2};
	CharmanderT = (PokemonType) {"Charmander", Fire, charmanderS, charmanderW, 39, 52, 43, 60, 50, 65, 2, grassTile, 4};
	PidgeyT = (PokemonType) {"Pidgey", Flying, pidgeyS, pidgeyW, 40, 45, 40, 35, 35, 56, 3, bothTile, 5};
	PikachuT = (PokemonType) {"Pikachu", Electric, pikachuS, pikachuW, 35, 55, 40, 50, 50, 90, 4, grassTile, 4};
	PsyduckT = (PokemonType) {"Psyduck", Water, psyduckS, psyduckW, 50, 52, 48, 65, 50, 55, 5, waterTile, 3};
	PonytaT = (PokemonType) {"Ponyta", Fire, ponytaS, ponytaW, 50, 85, 55, 65, 65, 90, 6, grassTile, 4};
	DratiniT = (PokemonType) {"Dratini", Dragon, dratiniS, dratiniW, 41, 64, 45, 50, 50, 50, 7, bothTile, 3};
	JigglypuffT = (PokemonType) {"Jigglypuff", Fairy, jigglypuffS, jigglypuffW, 115, 45, 20, 45, 25, 20, 8, bothTile, 3};
	VulpixT = (PokemonType) {"Vulpix", Fire, vulpixS, vulpixW, 38, 41, 40, 50, 65, 65, 9, grassTile, 5};
	EeveeT = (PokemonType) {"Eevee", Normal, eeveeS, eeveeW, 55, 55, 50, 45, 65, 55, 10, grassTile, 5};
	HorseaT = (PokemonType) {"Horsea", Water, horseaS, horseaW, 30, 40, 70, 70, 25, 60, 11, waterTile, 3};
	CuboneT = (PokemonType) {"Cubone", Ground, cuboneS, cuboneW, 50, 50, 95, 40, 50, 35, 12, grassTile, 5};
	ButterfreeT = (PokemonType) {"Butterfree", Bug, butterfreeS, butterfreeW, 60, 45, 50, 90, 80, 70, 13, bothTile, 5};
	MeowthT = (PokemonType) {"Meowth", Normal, meowthS, meowthW, 40, 45, 35, 40, 40, 90, 14, grassTile, 5};
	NidoranT = (PokemonType) {"Nidoran", Poison, nidoranS, nidoranW, 46, 57, 40, 40, 40, 50, 15, grassTile, 5};
	AbraT = (PokemonType) {"Abra", Psychic, abraS, abraW, 25, 20, 15, 105, 55, 90, 16, waterTile, 4};
	GhastlyT = (PokemonType) {"Gastly", Ghost, ghastlyS, ghastlyW, 30, 35, 30, 100, 35, 80, 17, waterTile, 5};
	MachampT = (PokemonType) {"Machop", Fighting, machampS, machampW, 70, 80, 50, 35, 35, 35, 18, grassTile, 4};
	GeodudeT = (PokemonType) {"Geodude", Rock, geodudeS, geodudeW, 40, 80, 100, 30, 30, 20, 19, grassTile, 4};
	
	allPokemon[0] = BulbasaurT;
	allPokemon[1] = SquirtleT;
	allPokemon[2] = CharmanderT;
	allPokemon[3] = PidgeyT;
	allPokemon[4] = PikachuT;
	allPokemon[5] = PsyduckT;
	allPokemon[6] = PonytaT;
	allPokemon[7] = DratiniT;
	allPokemon[8] = JigglypuffT;
	allPokemon[9] = VulpixT;
	allPokemon[10] = EeveeT;
	allPokemon[11] = HorseaT;
	allPokemon[12] = CuboneT;
	allPokemon[13] = ButterfreeT;
	allPokemon[14] = MeowthT;
	allPokemon[15] = NidoranT;
	allPokemon[16] = AbraT;
	allPokemon[17] = GhastlyT;
	allPokemon[18] = MachampT;
	allPokemon[19] = GeodudeT;
}

void IncSeed(){
	if(seedTimer){
		randomSeed ++;
	}else {
		if(randomSeed == 0) randomSeed = 1;
		NVIC_DIS1_R = 1<<19; // disable IRQ 19 in NVIC
	}
}

uint8_t DrawLanguageSelection(){
	Timer1_Init(IncSeed, 500);
	ST7735_FillScreen(0x0000);
	
	char *langs[2];
	langs[0] = "English";
	langs[1] = "Espanol";
	
	int8_t output = DrawSimpleMenu(langs, 2, false);
	
	seedTimer = false;
	Random_Init(randomSeed);
	if(output >= 0) return output;
	return 0;
}

PokemonType DrawTitleScreen(uint8_t language){
	PokemonType starters[3] = {BulbasaurT, SquirtleT, CharmanderT};
	SpriteInstType starterInsts[3];
	
	uint8_t starterYPos = 145;
	uint8_t starterXPos = 2;
	uint8_t starterXSep = 42;
	
	for(uint8_t i=0; i<3; i++){
		starterInsts[i] = (SpriteInstType) {starterXPos+i*starterXSep, starterYPos, starters[i].sprite};
	}
	
	SpriteSelectType starterScreen = {starterInsts, 3, 0};
	ST7735_FillScreen(0xFFFF);
	
	DrawAllSprites(starterScreen);
	
	SpriteType pokemonTitleS; 
	if(language) pokemonTitleS = (SpriteType) {pokemonnameSpanish, 128, 54};
	else pokemonTitleS = (SpriteType) {pokemonname, 128, 54};
	SpriteInstType pokemonTitle = {0, pokemonTitleS.height+10, pokemonTitleS};
	DrawSpriteImg(pokemonTitle);
	
	ST7735_SetTextColor(ST7735_BLACK);
	ST7735_SetCursor(1, 7);
	if(language) ST7735_OutString("Seleccione su\n entrante");
	else ST7735_OutString("Please select your\n starter.");
	
	while(1){
		
		while(ADCStatus == 0){}
		
		uint8_t xDir = getJoystickX();
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

void MoveWorldPokemon(){
	const uint8_t waitCooldown = 5;
	
	for(uint8_t i=0; i<numWorldPokemon; i++){
		uint8_t moveDir = Random()%40;
		bool moved = true;
		
		if(WorldPokemons[i].numWait > 0){
			WorldPokemons[i].numWait--;
			continue;
		}
		
		if(moveDir == 0){ //up
			if(IsPokemonWalkable(WorldPokemons[i].yPos-1, WorldPokemons[i].xPos, WorldPokemons[i].yPos, WorldPokemons[i].xPos, i)){
				WorldPokemons[i].yPos --;
				WorldPokemons[i].flip = false;
			}
		}else if(moveDir == 1){ //down
			if(IsPokemonWalkable(WorldPokemons[i].yPos+1, WorldPokemons[i].xPos, WorldPokemons[i].yPos, WorldPokemons[i].xPos, i)){
				WorldPokemons[i].yPos ++;
				WorldPokemons[i].flip = true;
			}
		}else if(moveDir == 2){ //left
			if(IsPokemonWalkable(WorldPokemons[i].yPos, WorldPokemons[i].xPos-1, WorldPokemons[i].yPos, WorldPokemons[i].xPos, i)){
				WorldPokemons[i].xPos --;
				WorldPokemons[i].flip = false;
			}
		}else if(moveDir == 3){ //right
			if(IsPokemonWalkable(WorldPokemons[i].yPos, WorldPokemons[i].xPos+1, WorldPokemons[i].yPos, WorldPokemons[i].xPos, i)){
				WorldPokemons[i].xPos ++;
				WorldPokemons[i].flip = true;
			}
		}else {
			moved = false;
			if(WorldPokemons[i].numWait > 0) WorldPokemons[i].numWait--;
		}
		
		if(moved) WorldPokemons[i].numWait = waitCooldown;
	}
}

bool PokemonLocationTaken(uint8_t xPos, uint8_t yPos, uint8_t index){
	for(int i=0; i<index; i++){
		if(WorldPokemons[i].xPos == xPos && WorldPokemons[i].yPos == yPos) return true;
	}
	return false;
}

PokemonInstType GenerateRandomPokemonInit(uint8_t index){
	uint8_t pokemon = Random()%numPokemonSpecies;
	uint8_t xPos = 0;
	uint8_t yPos = 0;
	while(!IsWalkable(yPos, xPos) || (xPos == p1.XPos && yPos == p1.YPos) || PokemonLocationTaken(xPos, yPos, index)){
		xPos = Random()%(FIELD_WIDTH-8) + 4;
		yPos = Random()%(FIELD_HEIGHT-10) + 5;
	}
	return (PokemonInstType) {xPos, yPos, allPokemon[pokemon].mhealth, allPokemon[pokemon], false, 0, allPokemon[pokemon].menergy};
}

GridCoordinateType GetPokemonGrid(uint8_t gridType){
	if(gridType == grassTile){
		uint32_t count = grassGridsLength;
		uint32_t gridIndex = Random32()%count;
		return grassGrids[gridIndex];
	}else if(gridType == waterTile){
		uint32_t count = waterGridsLength;
		uint32_t gridIndex = Random32()%count;
		return waterGrids[gridIndex];
	}else{
		uint32_t count = waterGridsLength + grassGridsLength;
		uint32_t gridIndex = Random32()%count;
		if(gridIndex < grassGridsLength){
			return grassGrids[gridIndex];
		}else {
			return waterGrids[gridIndex-grassGridsLength];
		}
	}
}

bool IsPokemonPosOnEdge(uint8_t xPos, uint8_t yPos){
	if(xPos < 4 || xPos >= FIELD_WIDTH-4 || yPos < 5 || yPos >= FIELD_HEIGHT-5) return true;
	return false;
}

PokemonInstType GenerateRandomPokemon(uint8_t index){
	uint8_t pokemon = Random()%numPokemonSpecies;
	PokemonType pokemonType = allPokemon[pokemon];
	
	uint8_t xPos = 0;
	uint8_t yPos = 0;
	while(!IsPokemonWalkable(yPos, xPos, yPos, xPos, index) || (xPos == p1.XPos && yPos == p1.YPos) || IsPokemonPosOnEdge(xPos, yPos)){
		GridCoordinateType randomCoordinate = GetPokemonGrid(pokemonType.tileType);
		xPos = randomCoordinate.col;
		yPos = randomCoordinate.row;
	}
	return (PokemonInstType) {xPos, yPos, allPokemon[pokemon].mhealth, allPokemon[pokemon], false, 0, allPokemon[pokemon].menergy};
}

bool DrawWorld(uint8_t language){
	
	const uint32_t movePokemonTime = 6666666;
	for(uint8_t i=0; i<numWorldPokemon; i++){
		WorldPokemons[i] = GenerateRandomPokemonInit(i);
		numWorldInstantiated ++;
	}
	Timer1_Init(MoveWorldPokemon, movePokemonTime);
	
	//draws black border around the edges of the screen
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
		
		if(xDir == 0){
			MoveLeft();
		}else if(xDir == 2){
			MoveRight();
		}else if(yDir == 0){
			MoveUp();
		}else if(yDir == 2){
			MoveDown();
		}
		
		DrawField();
		int8_t encounter = BumpedIntoWorldPokemon();
		if(encounter > -1){
			NVIC_DIS1_R = 1<<19; // disable IRQ 19 in NVIC
			ClearScreenGrid();
			DrawBattleScreen(&pokeTeam.pokemon[0], &WorldPokemons[encounter], language);
			WorldPokemons[encounter] = GenerateRandomPokemon(encounter);
			Timer1_Init(MoveWorldPokemon, movePokemonTime);
		}
		//uint8_t encounter = Random()%6;
		//if(moved && encounter == 0 && (GetFieldGrid(p1.YPos, p1.XPos) == W || GetFieldGrid(p1.YPos, p1.XPos) == G)){
			//ClearScreenGrid();
			//uint8_t pokemonRan = Random()%11;
			//PokemonType selected = allPokemon[pokemonRan];
			//DrawBattleScreen(&playerTeam[0], &selected, language);
		//}
		
		if(isPE2Pressed()){
			DrawStatusScreen(language);
		}else if(isPE3Pressed()){
			if(GetObjGrid(p1.YPos-1, p1.XPos) == S){
				ClearScreenGrid();
				SpriteSelectType shopScreen = {itemInsts, 3, 0};
				DrawShopScreen(&p1, playerInventory, shopScreen, shopItems, language);
			}
		}
	}
}

void DrawStatusScreen(uint8_t language){
	ClearScreenGrid();
	ST7735_FillScreen(0xFFFF);
			
	ST7735_SetCursor(1, 3);
	if(language) ST7735_OutString("Monedas: ");
	else ST7735_OutString("Coins: ");
	LCD_OutDec(p1.coins);
	ST7735_OutString("C");
			
	ST7735_SetCursor(1, 4);
	if(language) ST7735_OutString("Felicidad: ");
	else ST7735_OutString("Happiness: ");
	LCD_OutDec(p1.happiness);
	ST7735_OutString("/100");
	
	ST7735_SetCursor(1, 7);
	ST7735_OutString("Pokemon Team: \n ");
	for(int i = 0; i < pokeTeam.size; i++){
		ST7735_OutString(pokeTeam.pokemon[i].species.name);
		ST7735_OutString(" - ");
		LCD_OutDec(pokeTeam.pokemon[i].chealth);
		ST7735_OutString(" HP \n ");
	}
	
	while(1){
		if(isPE2Pressed()) break;
	}
}

bool PokemonAllDead(void){
	for(int i = 0; i < pokeTeam.size; i++){
		if(pokeTeam.pokemon[i].chealth > 0){
			return false;
		}
	}
	return true;
}

	uint8_t pokeBattleLeftX = 2;
	uint8_t pokeBattleRightX = 86;
	uint8_t pokeBattleY = 90;

void DrawHPBars(PokemonInstType* pokeLeft, PokemonInstType* pokeRight){
	uint32_t lowColor = 0x00FF;
	uint32_t highColor = 0x0FF0;
	
	uint32_t lColor = highColor;
	uint32_t rColor = highColor;
	
	if(pokeLeft->chealth <= pokeLeft->species.mhealth/2) lColor = lowColor;
	if(pokeRight->chealth <= pokeRight->species.mhealth/2) rColor = lowColor;
	
	ST7735_FillRect(pokeBattleLeftX+5, 35, 30, 2, 0x0000);
	ST7735_FillRect(pokeBattleRightX+5, 25, 30, 2, 0x0000);
	
	ST7735_FillRect(pokeBattleLeftX+5, 35, pokeLeft->chealth*30/pokeLeft->species.mhealth, 2, lColor);
	ST7735_FillRect(pokeBattleRightX+5, 25, pokeRight->chealth*30/pokeRight->species.mhealth, 2, rColor);
}

void DrawEPBars(PokemonInstType* pokeLeft, PokemonInstType* pokeRight){
	ST7735_FillRect(pokeBattleLeftX+5, 40, 30, 2, 0x0000);
	ST7735_FillRect(pokeBattleRightX+5, 30, 30, 2, 0x0000);
	
	ST7735_FillRect(pokeBattleLeftX+5, 40, pokeLeft->cenergy*30/pokeLeft->species.menergy, 2, 0xFF00);
	ST7735_FillRect(pokeBattleRightX+5, 30, pokeRight->cenergy*30/pokeRight->species.menergy, 2, 0xFF00);
}

void RestoreDeadPokemon(void){
	for(int i = 0; i < pokeTeam.size; i++){
		if(pokeTeam.pokemon[i].chealth == 0){
			pokeTeam.pokemon[i].chealth = 1;
		}
	}
}

void DrawPokemonNames(PokemonInstType* pokeLeft, PokemonInstType* pokeRight){
	
	ST7735_FillRect(0, 0, 72, 30, 0xFFFF);
	ST7735_SetCursor(1, 2);
	ST7735_OutString(pokeLeft->species.name);
	
	uint8_t length = 0;
	while(pokeRight->species.name[length] != 0x0000){
		length++;
	}
	
	ST7735_SetCursor(20-length, 4);
	ST7735_OutString(pokeRight->species.name);
}
	
void DrawBattleScreen(PokemonInstType* pokeLeft, PokemonInstType* pokeRight, uint8_t language){
	
	ST7735_FillScreen(0xFFFF);
	uint8_t pokeBattleLeftX = 2;
	uint8_t pokeBattleRightX = 86;
	uint8_t pokeBattleY = 90;
	
	pokeLeft->xPos = pokeBattleLeftX;
	pokeLeft->yPos = pokeBattleY;
	pokeRight->xPos = pokeBattleRightX;
	pokeRight->yPos = pokeBattleY;
	SpriteInstType leftInst = (SpriteInstType) {2, 90, pokeLeft->species.sprite};
	SpriteInstType rightInst = (SpriteInstType) {86, 90, pokeRight->species.sprite};
	
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
	}else{
		runText = (SpriteType){run, 32, 16};
	}
	SpriteInstType runInst = {84, 150, runText};
	
	SpriteInstType battleCommands[4] = {fightInst, itemInst, pokeInst, runInst};
	SpriteSelectType battleScreen = {battleCommands, 4, 0};
	DrawAllSprites(battleScreen);
	
	DrawHPBars(pokeLeft, pokeRight);
	DrawEPBars(pokeLeft, pokeRight);
	DrawPokemonNames(pokeLeft, pokeRight);
	
	while(1){
		
		while(ADCStatus == 0){}
		// Get input from joystick
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
			if(battleScreen.currentIndex == 3){ // Run
				break;
			}else if(battleScreen.currentIndex == 1){ // Item
				if(DrawBattleInventory(pokeLeft, pokeRight, language)){
					pokeTeam.currIndex = 0;
					RestoreDeadPokemon();
					break;
				}
				ST7735_FillRect(0, 100, 128, 60, 0xFFFF);
				DrawAllSprites(battleScreen);
			}else if (battleScreen.currentIndex == 2){ // Pokemon
				pokeLeft = DrawPokemonInventory(language);
				leftInst = (SpriteInstType) {2, 90, pokeLeft->species.sprite};
				DrawSpriteImg(leftInst);
				DrawHPBars(pokeLeft, pokeRight);
				DrawEPBars(pokeLeft, pokeRight);
				DrawAllSprites(battleScreen);
				DrawPokemonNames(pokeLeft, pokeRight);
			}else if(battleScreen.currentIndex == 0){ // Fight
				int results = DrawMoveCommands(pokeLeft, pokeRight, language);
				if(results == 0) DrawAllSprites(battleScreen);
				else{
					if(results == 1){
						ST7735_SetCursor(1, 12);
						if(language) ST7735_OutString("Salvaje ");
						else ST7735_OutString("Wild ");
						ST7735_OutString(pokeRight->species.name);
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
						pokeTeam.currIndex = 0;
						RestoreDeadPokemon();
						while(1) if(isPE3Pressed()) break;
						break;
					}else {
						ST7735_SetCursor(1, 12);
						if(language) ST7735_OutString("Tu ");
						else ST7735_OutString("Your ");
						ST7735_OutString(pokeLeft->species.name);
						if(language) ST7735_OutString("\n desmayado.");
						else ST7735_OutString("\n fainted.");
						while(1) if(isPE3Pressed()) break;
						ST7735_FillRect(0, 94, 128, 56, 0xFFFF);
						if(PokemonAllDead()){ // Ran out of pokemon (lost game)
							ST7735_SetCursor(1, 12);
							if(language) ST7735_OutString("Tu felicidad\n cay\xA2 por 10.");
							else ST7735_OutString("Your happiness\n dropped by 10.");
							uint8_t drop = 10;
							if(p1.happiness < 10) drop = p1.happiness;
							p1.happiness -= drop;
							pokeTeam.currIndex = 0;
							RestoreDeadPokemon();
							while(1) if(isPE3Pressed()) break;
							break;
						} // otherwise, game continues with next pokemon in team
						pokeLeft = DrawPokemonInventory(language);
						leftInst = (SpriteInstType) {2, 90, pokeLeft->species.sprite};
						DrawSpriteImg(leftInst);
						DrawHPBars(pokeLeft, pokeRight);
						DrawEPBars(pokeLeft, pokeRight);
						DrawAllSprites(battleScreen);
						DrawPokemonNames(pokeLeft, pokeRight);
					}
				}
			}
		}
  }
}

PokemonInstType* DrawPokemonInventory(uint8_t language){
	ST7735_FillRect(0, 100, 128, 60, 0xFFFF);
	PokemonInstType alivePokemon[6];
	uint32_t aliveIndex[6];
	uint32_t numAlive = 0;
	for(int i = 0; i < pokeTeam.size; i++){
		if(pokeTeam.pokemon[i].chealth > 0){
			alivePokemon[numAlive] = pokeTeam.pokemon[i];
			aliveIndex[numAlive] = i;
			numAlive++;
		}
	}
	char *a[7];
	int selected = 0;
	for(int i=0; i<numAlive; i++){
		a[i] = alivePokemon[i].species.name;
	}
	
	for(int i=0; i<numAlive; i++){
			ST7735_SetCursor(3, 10+i);
			ST7735_OutString(a[i]);
	}
	
	while(1){
		while(ADCStatus == 0){}
			
		uint8_t yDir = getJoystickY();
		ADCStatus = 0;
		
		if(yDir == 2 && selected < numAlive-1){
			selected++;
		}else if(yDir == 0 && selected > 0){
			selected--;
		}
		
		for(int i=0; i<numAlive; i++){
			ST7735_SetCursor(1, 10+i);
			if(i==selected) ST7735_OutString("*");
			else ST7735_OutString(" ");
		}
		
		if(isPE2Pressed()){
			ST7735_FillRect(0, 100, 128, 60, 0xFFFF);
			return &pokeTeam.pokemon[pokeTeam.currIndex];
		}
		
		if(isPE3Pressed()){
			ST7735_FillRect(0, 100, 128, 60, 0xFFFF);
			ST7735_SetCursor(1, 12);
			ST7735_OutString(pokeTeam.pokemon[pokeTeam.currIndex].species.name);
			if(language) ST7735_OutString("\n intercambiado\n por ");
			else ST7735_OutString(" swapped\n for ");
			ST7735_OutString(pokeTeam.pokemon[aliveIndex[selected]].species.name);
			while(1){if(isPE3Pressed()) break;};
			pokeTeam.currIndex = aliveIndex[selected];
			ST7735_FillRect(0, 100, 128, 60, 0xFFFF);
			return &pokeTeam.pokemon[aliveIndex[selected]];
		}
	}
}

void DrawSwapPokemon(uint8_t language, PokemonInstType* pokeRight){
	ST7735_FillRect(0, 100, 128, 60, 0xFFFF);
	
	char *a[6];
	int selected = 0;
	for(int i=0; i<pokeTeam.size; i++){
		a[i] = pokeTeam.pokemon[i].species.name;
	}
	
	for(int i=0; i<pokeTeam.size; i++){
			ST7735_SetCursor(3, 10+i);
			ST7735_OutString(a[i]);
	}
	ST7735_SetCursor(1, 15);
	
	while(1){
		while(ADCStatus == 0){}
			
		uint8_t yDir = getJoystickY();
		ADCStatus = 0;
		
		if(yDir == 2 && selected < 5){
			selected++;
		}else if(yDir == 0 && selected > 0){
			selected--;
		}
		
		for(int i=0; i<pokeTeam.size; i++){
			ST7735_SetCursor(1, 10+i);
			if(i==selected) ST7735_OutString("*");
			else ST7735_OutString(" ");
		}
		
		if(isPE2Pressed()){
			return;
		}
		
		if(isPE3Pressed()){
			ST7735_FillRect(0, 100, 128, 60, 0xFFFF);
			ST7735_SetCursor(1, 12);
			ST7735_OutString(pokeRight->species.name);
			if(language) ST7735_OutString(" intercambiado\n por ");
			else ST7735_OutString(" swapped\n for ");
			ST7735_OutString(pokeTeam.pokemon[selected].species.name);
			while(1){if(isPE3Pressed()) break;};
			addPokemon(pokeRight, selected);
			return;
		}
	}
}

uint8_t DrawBattleInventory(PokemonInstType* pokeLeft, PokemonInstType* pokeRight, uint8_t language){
	ST7735_FillRect(0, 100, 128, 60, 0xFFFF);
	uint8_t numItems = 2;
	char *a[2];
	int selected = 0;
	for(int i=0; i<numItems; i++){
		a[i] = shopItems[i].item.name[language];
	}
	
	for(int i=0; i<numItems; i++){
			ST7735_SetCursor(3, 12+i);
			ST7735_OutString(a[i]);
			if(i!=3) ST7735_OutString(" x");
			if(i!=3) ST7735_OutChar((char) (playerInventory[i].count + 0x30));
	}
	
	while(1){
		while(ADCStatus == 0){}
			
		uint8_t yDir = getJoystickY();
		ADCStatus = 0;
		
		if(yDir == 2 && selected < numItems - 1){
			selected++;
		}else if(yDir == 0 && selected > 0){
			selected--;
		}
		
		for(int i=0; i<numItems; i++){
			ST7735_SetCursor(1, 12+i);
			if(i==selected) ST7735_OutString("*");
			else ST7735_OutString(" ");
		}
		
		if(isPE2Pressed()){
			ST7735_FillRect(0, 100, 128, 60, 0xFFFF);
			return 0;
		}
		
		if(isPE3Pressed()){
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
						//play sound
						Sound_Heal();
						while(soundStatus == 0){}
						soundStatus = 0;
						ST7735_OutString(pokeLeft->species.name);
						if(language) ST7735_OutString("ha sido \n curado");
						else ST7735_OutString(" has been \n healed.");
						pokeLeft->chealth = pokeLeft->species.mhealth;
						pokeLeft->cenergy = pokeLeft->species.menergy;
						DrawHPBars(pokeLeft, pokeRight);
						DrawEPBars(pokeLeft, pokeRight);
						while(1){if(isPE3Pressed()) break;};
					}else if(selected == 0){ // Using pokeball
						ST7735_SetCursor(1, 12);
						ST7735_FillRect(0, 100, 128, 60, 0xFFFF);
						if(pokeRight->chealth > pokeRight->species.mhealth/2){ // Failed catch
							if(language) ST7735_OutString("Pokebola no\n pudo atrapar");
							else ST7735_OutString("Pokeball failed\n to catch");
							ST7735_SetCursor(1, 14);
							ST7735_OutString(pokeRight->species.name);
							while(1){if(isPE3Pressed()) break;};
						}
						else{ // Successful catch
							if(language) ST7735_OutString("Has atrapado");
						  else ST7735_OutString("You have caught");
							ST7735_SetCursor(1, 13);
						  ST7735_OutString(pokeRight->species.name);
							while(1){if(isPE3Pressed()) break;};
							if(pokeTeam.size < 6){
								addPokemon(pokeRight, pokeTeam.size);
								return 1;
							}
							ST7735_SetCursor(1, 12);
							ST7735_FillRect(0, 100, 128, 60, 0xFFFF);
							if(language) ST7735_OutString("Tu inventario de pokemon\n \x82sta lleno. Por favor elige\n a un pokemon para\n intercambiar");
						  else ST7735_OutString("Your pokemon\n inventory is full.\n Please choose\n a pokemon to swap.");
							while(1){if(isPE3Pressed()) break;};
							DrawSwapPokemon(language, pokeRight);
							return 1;
						}
					}
				}else { // Don't have selected item
					if(language) ST7735_OutString("No tienes ninguno\n ");
					else ST7735_OutString("You don't have any\n ");
					ST7735_OutString(a[selected]);
					while(1){if(isPE3Pressed()) break;};
				}
				ST7735_FillRect(0, 100, 128, 60, 0xFFFF);
				for(int i=0; i<numItems; i++){
					ST7735_SetCursor(3, 12+i);
					ST7735_OutString(a[i]);
					if(i!=3) ST7735_OutString(" x");
					if(i!=3) ST7735_OutChar((char) (playerInventory[i].count + 0x30));
				}
		}
	}
}

SpriteInstType pokeShakeInst;

int8_t curX = 0;

bool timerOn = false;
void moveShakeLeft(){
	if(curX >= -10){
		ST7735_FillRect(pokeShakeInst.x_left, pokeShakeInst.y_bottom-pokeShakeInst.sprite.height-1, pokeShakeInst.sprite.width, pokeShakeInst.sprite.height, 0xFFFF);
		pokeShakeInst.x_left --;
		DrawSpriteImg(pokeShakeInst);
		curX--;
	}else {
		NVIC_DIS1_R = 1<<19; 
		timerOn = false;
	}
}

void moveShakeRight(){
	if(curX <= 10){
		ST7735_FillRect(pokeShakeInst.x_left, pokeShakeInst.y_bottom-pokeShakeInst.sprite.height-1, pokeShakeInst.sprite.width, pokeShakeInst.sprite.height, 0xFFFF);
		pokeShakeInst.x_left ++;
		DrawSpriteImg(pokeShakeInst);
		curX++;
	}else {
		NVIC_DIS1_R = 1<<19; 
		timerOn = false;
	}
}

void moveShakeBack(){
	if(curX > 0){
		ST7735_FillRect(pokeShakeInst.x_left, pokeShakeInst.y_bottom-pokeShakeInst.sprite.height-1, pokeShakeInst.sprite.width, pokeShakeInst.sprite.height, 0xFFFF);
		pokeShakeInst.x_left --;
		DrawSpriteImg(pokeShakeInst);
		curX--;
	}else if(curX < 0){
		ST7735_FillRect(pokeShakeInst.x_left, pokeShakeInst.y_bottom-pokeShakeInst.sprite.height-1, pokeShakeInst.sprite.width, pokeShakeInst.sprite.height, 0xFFFF);
		pokeShakeInst.x_left ++;
		DrawSpriteImg(pokeShakeInst);
		curX++;
	}else {
		NVIC_DIS1_R = 1<<19; 
		timerOn = false;
	}
}

uint8_t DrawMoveCommands(PokemonInstType* pokeLeft, PokemonInstType* pokeRight, uint8_t language){
	
	// Initialize moves for both pokemon
	ST7735_FillRect(10, 104, 106, 46, 0xFFFF);
	MoveType normal = NormalMoves[pokeLeft->species.moveSet];
	MoveType signature = SignatureMoves[pokeLeft->species.moveSet];
	uint8_t selected = 0;
	char *a[2];
	a[0] = normal.name[language];
	a[1] = signature.name[language];
	
	for(int i=0; i<2; i++){
			ST7735_SetCursor(3, 12+i);
			ST7735_OutString(a[i]);
	}
	
	SpriteInstType leftInst = (SpriteInstType) {2, 90, pokeLeft->species.sprite};
	SpriteInstType rightInst = (SpriteInstType) {86, 90, pokeRight->species.sprite};
	
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
		
		if(isPE2Pressed()){
			ST7735_FillRect(0, 104, 116, 46, 0xFFFF);
			return 0;
		}
		
		if(isPE3Pressed()){
			// Execute move
			MoveType selectedMove;
			if(selected == 0){
				selectedMove = normal;
			}else if(selected == 1){
				selectedMove = signature;
			}
			
			if(selected == 1 && pokeLeft->cenergy <= 0){
				ST7735_FillRect(0, 104, 116, 46, 0xFFFF);
				ST7735_SetCursor(1, 12);
				ST7735_OutString(pokeLeft->species.name);
				if(language) ST7735_OutString(" no le queda\n energía.");
				else ST7735_OutString(" does\n not have any\n energy left.");
				while(1) {if(isPE3Pressed()) break;}
				ST7735_FillRect(0, 104, 128, 46, 0xFFFF);
				return DrawMoveCommands(pokeLeft, pokeRight, language);
			}else if(selected == 1) {
				pokeLeft->cenergy --;
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
			}else{
				if(language) ST7735_OutString("Fue\n decentemente\n efectivo.");
				else ST7735_OutString("It was\n decently effective.");
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
			
			// Calculate damage
			uint8_t randomDamMul = Random()%25;
			uint32_t damage = ((8*attack*selectedMove.power/defense)/20 + 2)*(effectiveness*(75+randomDamMul))/2/100 + 1;
			if(damage > pokeRight->chealth) damage = pokeRight->chealth;
			pokeRight->chealth = pokeRight->chealth - damage;
			
			DrawHPBars(pokeLeft, pokeRight);
			DrawEPBars(pokeLeft, pokeRight);
		
			//play sound
		if(selected == 0){
			Sound_Attack1();
		}else {
			Sound_Attack2();
		}
		while(soundStatus == 0){}
		soundStatus = 0;
				
			pokeShakeInst = rightInst;
		
		// Battle animations
		for(int i=0; i<3; i++){
			timerOn = true;
			Timer1_Init(moveShakeLeft, 20000);
			while(timerOn){}
			timerOn = true;
			Timer1_Init(moveShakeRight, 20000);	
			while(timerOn){}
		}
		timerOn = true;
		Timer1_Init(moveShakeBack, 20000);	
		while(timerOn){}
		DrawSpriteImg(pokeShakeInst);
		while(1) {if(isPE3Pressed()) break;}
				
		//Opponent pokemon attack
		if(pokeRight->chealth == 0) {
			ST7735_FillRect(0, 94, 128, 56, 0xFFFF);
			return 1;
		}
				
		uint8_t movePool = 2;
		
		if(pokeRight->cenergy <= 0) movePool = 1;
		bool useNormal = Random()%movePool == 0;
		if(useNormal){
			selectedMove = NormalMoves[pokeRight->species.moveSet];
		}else {
			selectedMove = SignatureMoves[pokeRight->species.moveSet];
			pokeRight->cenergy --;
		}
				
		ST7735_FillRect(0, 104, 116, 46, 0xFFFF);
		ST7735_SetCursor(1, 12);
		ST7735_OutString(pokeRight->species.name);
		if(language) ST7735_OutString(" usado \n ");
		else ST7735_OutString(" used \n ");
		ST7735_OutString(selectedMove.name[language]);
		while(1) {if(isPE3Pressed()) break;}
				
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
			if(language) ST7735_OutString("Fue\n decentemente\n efectivo.");
			else ST7735_OutString("It was\n decently effective.");
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
				
		DrawHPBars(pokeLeft, pokeRight);
		DrawEPBars(pokeLeft, pokeRight);
				
		//play sound
		if(useNormal){
			Sound_Attack1();
		}else {
			Sound_Attack2();
		}
		while(soundStatus == 0){}
		soundStatus = 0;
				
		pokeShakeInst = leftInst;
		
		for(int i=0; i<3; i++){
			timerOn = true;
			Timer1_Init(moveShakeLeft, 20000);
			while(timerOn){}
			timerOn = true;
			Timer1_Init(moveShakeRight, 20000);	
			while(timerOn){}
		}
		timerOn = true;
		Timer1_Init(moveShakeBack, 20000);	
		while(timerOn){}
			
		DrawSpriteImg(pokeShakeInst);
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

int8_t DrawSimpleMenu(char *menuItems[], uint8_t menuLength, bool useBack){
	ST7735_FillRect(0, simpleMenuY, _width, _height-simpleMenuY, simpleMenuColor);
	int selected = 0;
	
	uint8_t yStrLine = 12;
	char selection = '*';
	
	for(int i=0; i<menuLength; i++){
			ST7735_SetCursor(3, yStrLine+i);
			ST7735_OutString(menuItems[i]);
	}
	
	while(1){
		while(ADCStatus == 0){}
			
		uint8_t yDir = getJoystickY();
		ADCStatus = 0;
		
		if(yDir == 2 && selected < menuLength-1){
			selected++;
		}else if(yDir == 0 && selected > 0){
			selected--;
		}
		
		for(int i=0; i<menuLength; i++){
			ST7735_SetCursor(1, yStrLine+i);
			if(i==selected) ST7735_OutChar(selection);
			else ST7735_OutChar(' ');
		}
		
		if(isPE3Pressed()){
			return selected;
		}else if(isPE2Pressed() && useBack){
			return backReturn;
		}
	}
}
