
#include "PokemonType.h"
#include "Field.h"
#include "ImagesPokemon2.h"
#include "ImagesPokemonWorld.h"
#include "Random.h"
#include "Player.h"

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

uint32_t numPokemonSpecies = 20;
PokemonType allPokemon[20];


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

bool PokemonLocationTaken(uint8_t xPos, uint8_t yPos, uint8_t index){
	for(int i=0; i<index; i++){
		if(WorldPokemons[i].xPos == xPos && WorldPokemons[i].yPos == yPos) return true;
	}
	return false;
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
