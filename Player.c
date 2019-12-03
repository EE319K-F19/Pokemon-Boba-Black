
#include <stdbool.h>
#include "Field.h"
#include "ImagesOther.h"
#include "Player.h"
#include "Shop.h"
#include "ST7735.h"
#include "StructDec.h"
#include "SystemInfo.h"
#include "DrawScreen.h"
#include <stdlib.h>

PlayerType p1;
ItemInventoryType playerInventory[3];
PokemonInstType* playerTeam;
PokemonTeamType pokeTeam;

void InitPlayer(){
	SpriteType PlayerFront = {playerFront, 16, 16};
	SpriteType PlayerBack = {playerBack, 16, 16};
	SpriteType PlayerSide = {playerSide, 16, 16};
	
	SpriteType PlayerSwimFront = {playerSwimFront, 16, 16};
	SpriteType PlayerSwimBack = {playerSwimBack, 16, 16};
	SpriteType PlayerSwimSide = {playerSwimSide, 16, 16};
	
	p1 = (PlayerType) {14, 7, PlayerFront, PlayerFront, PlayerBack, PlayerSide, PlayerSwimFront, PlayerSwimBack, PlayerSwimSide, 25, 25, false};
}

void InitInventory(){
	playerInventory[0] = (ItemInventoryType) {pokeballItem, 0};
	playerInventory[1] = (ItemInventoryType) {potionItem, 0};
	playerInventory[2] = (ItemInventoryType) {bobaItem, 0};
}

void InitTeam(){
	pokeTeam.currIndex = 0;
	pokeTeam.size = 0;
	//pokeTeam->pokemon = (PokemonInstType*)malloc(sizeof(PokemonInstType)*6);
}

void StartTeam(){
	pokeTeam.currIndex = 0;
	pokeTeam.size = 6;
	pokeTeam.pokemon[0] = (PokemonInstType){0, 0, allPokemon[0].mhealth, allPokemon[0]};
	pokeTeam.pokemon[1] = (PokemonInstType){0, 0, allPokemon[1].mhealth, allPokemon[1]};
	pokeTeam.pokemon[2] = (PokemonInstType){0, 0, allPokemon[2].mhealth, allPokemon[2]};
	pokeTeam.pokemon[3] = (PokemonInstType){0, 0, allPokemon[3].mhealth, allPokemon[3]};
	pokeTeam.pokemon[4] = (PokemonInstType){0, 0, allPokemon[4].mhealth, allPokemon[4]};
	pokeTeam.pokemon[5] = (PokemonInstType){0, 0, allPokemon[5].mhealth, allPokemon[5]};
}

void DrinkBoba(){
	p1.happiness += 25;
}

void LoseBattle(){
	p1.happiness -= 10;
}

void addPokemon(PokemonInstType* newPokemon, uint32_t index){
	pokeTeam.pokemon[index].xPos = 0;
	pokeTeam.pokemon[index].yPos = 0;
	pokeTeam.pokemon[index].chealth = newPokemon->chealth;
	pokeTeam.pokemon[index].species = newPokemon->species;
	if(pokeTeam.size < 6){
		pokeTeam.size++;
	}
}

bool MoveUp(){
	if(GetFieldGrid(p1.YPos-1, p1.XPos) == W){
		p1.sprite = p1.spriteSwimBack;
	}else{
		p1.sprite = p1.spriteBack;
	}
	p1.flipped = false;
	if(IsWalkable(p1.YPos-1, p1.XPos)){
		p1.YPos --;
		return true;
	}
	return false;
}

bool MoveDown(){
	if(GetFieldGrid(p1.YPos+1, p1.XPos) == W){
		p1.sprite = p1.spriteSwimFront;
	}else{
		p1.sprite = p1.spriteFront;
	}
	p1.flipped = false;
	if(IsWalkable(p1.YPos+1, p1.XPos)){
		p1.YPos ++;
		return true;
	}
	return false;
}

bool MoveLeft(){
	if(GetFieldGrid(p1.YPos, p1.XPos-1) == W){
		p1.sprite = p1.spriteSwimSide;
	}else{
		p1.sprite = p1.spriteSide;
	}
	p1.flipped = false;
	if(IsWalkable(p1.YPos, p1.XPos-1)){
		p1.XPos --;
		return true;
	}
	return false;
}

bool MoveRight(){
	if(GetFieldGrid(p1.YPos, p1.XPos+1) == W){
		p1.sprite = p1.spriteSwimSide;
	}else{
		p1.sprite = p1.spriteSide;
	}
	p1.flipped = true;
	if(IsWalkable(p1.YPos, p1.XPos+1)){
		p1.XPos ++;
		return true;
	}
	return false;
}
