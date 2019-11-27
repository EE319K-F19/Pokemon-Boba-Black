
#ifndef _STRUCTDECH_
#define _STRUCTDECH_

#include <stdint.h>

typedef struct Sprite SpriteType;
typedef struct SpriteInst SpriteInstType;
typedef struct SpriteSelect SpriteSelectType;
typedef struct Pokemon PokemonType;
typedef struct PokemonInst PokemonInstType;
typedef struct Types TypeType;
typedef struct Field FieldType;
typedef struct PokemonTeam PokemonTeamType;
typedef struct Player PlayerType;
typedef struct Item ItemType;
typedef struct ItemInventory ItemInventoryType;
typedef struct itemInst ItemInstType;

struct Sprite {
	const uint16_t* image;	
	int16_t width; 
	int16_t height;
};

struct SpriteInst {
	int16_t x_left; 
	int16_t y_bottom;
	SpriteType sprite;
};

struct SpriteSelect {
	const SpriteInstType* spriteInsts;
	const uint16_t spriteArrayLength;
	int16_t currentIndex;
};

struct Pokemon {
	char *name;
	uint8_t type;
	SpriteType sprite;
	uint32_t mhealth;
	uint32_t attack;
	uint32_t defense;
	uint32_t spattack;
	uint32_t spdefense;
	uint32_t speed;
};

struct PokemonInst {
	uint16_t xPos;
	uint16_t yPos;
	uint32_t chealth;
	const PokemonType species;
};

struct Types {
	const uint8_t Normal; 
	const uint8_t Fire; 
	const uint8_t Water;
	const uint8_t Electric;
	const uint8_t Grass;
	const uint8_t Ice;
	const uint8_t Fighting;
	const uint8_t Poison;
	const uint8_t Ground;
	const uint8_t Flying;
	const uint8_t Psychic;
	const uint8_t Bug;
	const uint8_t Rock;
	const uint8_t Ghost;
	const uint8_t Dragon;
	const uint8_t Dark;
	const uint8_t Steel;
	const uint8_t Fairy;
};

struct Field {
	uint8_t *FieldArray;
	const uint32_t FieldWidth;
	const uint32_t FieldHeight;
};

struct PokemonTeam {
	PokemonInstType pokemon1;
	PokemonInstType pokemon2;
	PokemonInstType pokemon3;
	PokemonInstType pokemon4;
	PokemonInstType pokemon5;
	PokemonInstType pokemon6;
};

struct Player {
	uint32_t XPos;
	uint32_t YPos;
	
	SpriteType sprite;
	SpriteType spriteFront;
	SpriteType spriteBack;
	SpriteType spriteSide;
	SpriteType spriteLeft;
	uint32_t coins;
	uint32_t happiness;
	
	//PokemonTeamType team;
	// ItemInventoryType playerInventory[3];
};

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

#endif
