
#ifndef _STRUCTDECH_
#define _STRUCTDECH_

#include <stdbool.h>
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
typedef struct Move MoveType;
typedef struct GridCoordinate GridCoordinateType;

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

struct Move{
	char* name[2];
	uint8_t type;
	uint8_t category;
	uint8_t power;
};

struct GridCoordinate {
	uint8_t row;
	uint8_t col;
};

struct Pokemon {
	char *name;
	uint8_t type;
	SpriteType sprite;
	SpriteType worldSprite;
	uint32_t mhealth;
	uint32_t attack;
	uint32_t defense;
	uint32_t spattack;
	uint32_t spdefense;
	uint32_t speed;
	uint8_t moveSet;
	uint8_t tileType;
};

struct PokemonInst {
	uint16_t xPos;
	uint16_t yPos;
	uint32_t chealth;
	PokemonType species;
	bool flip;
	uint8_t numWait;
};

struct PokemonTeam {
PokemonInstType pokemon[6];
uint8_t size;
uint8_t currIndex;
};

struct Item {
	char* name[2];
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

struct Player {
	uint32_t XPos;
	uint32_t YPos;
	
	SpriteType sprite;
	SpriteType spriteFront;
	SpriteType spriteBack;
	SpriteType spriteSide;
	
	SpriteType spriteSwimFront;
	SpriteType spriteSwimBack;
	SpriteType spriteSwimSide;
	uint32_t coins;
	int32_t happiness;
	
	bool flipped;
};

#endif
