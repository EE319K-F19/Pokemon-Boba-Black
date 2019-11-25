
#include "Draw.h"
#include "Field.h"
typedef struct Pokemon PokemonType;
typedef struct PokemonInst PokemonInstType;

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

extern PokemonType BulbasaurT;
extern PokemonType SquirtleT;
extern PokemonType CharmanderT;
extern PokemonType PidgeyT;
extern PokemonType PikachuT;

void InitPokemon(void);
void DrawTitleScreen(SpriteSelectType starterScreen);
void DrawBattleScreen(PokemonInstType* pokeLeft, PokemonInstType* pokeRight);
void DrawWorld(PlayerType p1, FieldType mainField);
