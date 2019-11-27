
#include "Battle.h"
#include "StructDec.h"
#include "PokemonType.h"

const uint8_t CAT_PHYSICAL = 1;
const uint8_t CAT_SPECIAL = 2;

MoveType NormalMoves[100];
MoveType SignatureMoves[100];

void InitMoves(){
	NormalMoves[0] = (MoveType) {"Vine Whip", Grass, CAT_PHYSICAL, 45};
	SignatureMoves[0] = (MoveType) {"Petal Dance", Grass, CAT_SPECIAL, 120};
	
	NormalMoves[1] = (MoveType) {"Water Gun", Water, CAT_SPECIAL, 40};
	SignatureMoves[1] = (MoveType) {"Water Sprout", Water, CAT_SPECIAL, 150};
	
	NormalMoves[2] = (MoveType) {"Dragon Breath", Dragon, CAT_PHYSICAL, 60};
	SignatureMoves[2] = (MoveType) {"Inferno", Fire, CAT_SPECIAL, 100};
	
	NormalMoves[3] = (MoveType) {"Gust", Flying, CAT_SPECIAL, 40};
	SignatureMoves[3] = (MoveType) {"Razor Wind", Flying, CAT_SPECIAL, 80};
	
	NormalMoves[4] = (MoveType) {"Thunder Shock", Electric, CAT_SPECIAL, 40};
	SignatureMoves[4] = (MoveType) {"Thunder", Electric, CAT_SPECIAL, 110};
}

