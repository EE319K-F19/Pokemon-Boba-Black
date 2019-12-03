
#include "Battle.h"
#include "StructDec.h"
#include "PokemonType.h"

const uint8_t CAT_PHYSICAL = 1;
const uint8_t CAT_SPECIAL = 2;

MoveType NormalMoves[100];
MoveType SignatureMoves[100];

void InitMoves(){
	NormalMoves[0] = (MoveType) {{"Vine Whip", "Latigo Cepa"}, Grass, CAT_PHYSICAL, 45};
	SignatureMoves[0] = (MoveType) {{"Petal Dance", "Baile Petalo"}, Grass, CAT_SPECIAL, 120};
	
	NormalMoves[1] = (MoveType) {{"Water Gun", "Pistola de Agua"}, Water, CAT_SPECIAL, 40};
	SignatureMoves[1] = (MoveType) {{"Water Sprout", "Brote de Agua"}, Water, CAT_SPECIAL, 150};
	
	NormalMoves[2] = (MoveType) {{"Ember", "Ascua"}, Fire, CAT_SPECIAL, 40};
	SignatureMoves[2] = (MoveType) {{"Inferno", "Infierno"}, Fire, CAT_SPECIAL, 100};
	
	NormalMoves[3] = (MoveType) {{"Gust", "Rafaga"}, Flying, CAT_SPECIAL, 40};
	SignatureMoves[3] = (MoveType) {{"Razor Wind", "Viento Navaja"}, Flying, CAT_SPECIAL, 80};
	
	NormalMoves[4] = (MoveType) {{"Thunder Shock", "Choque de Trueno"}, Electric, CAT_SPECIAL, 40};
	SignatureMoves[4] = (MoveType) {{"Thunder", "Trueno"}, Electric, CAT_SPECIAL, 110};
}

