
#include "Battle.h"
#include "StructDec.h"
#include "PokemonType.h"

const uint8_t CAT_PHYSICAL = 1;
const uint8_t CAT_SPECIAL = 2;

MoveType NormalMoves[100];
MoveType SignatureMoves[100];

void InitMoves(){
	NormalMoves[0] = (MoveType) {{"Vine Whip", "L\xA0tigo Cepa"}, Grass, CAT_PHYSICAL, 45};
	SignatureMoves[0] = (MoveType) {{"Petal Dance", "Baile P\x82talo"}, Grass, CAT_SPECIAL, 120};

	NormalMoves[1] = (MoveType) {{"Water Gun", "Pistola de Agua"}, Water, CAT_SPECIAL, 40};
	SignatureMoves[1] = (MoveType) {{"Water Sprout", "Brote de Agua"}, Water, CAT_SPECIAL, 150};

	NormalMoves[2] = (MoveType) {{"Ember", "Ascua"}, Fire, CAT_SPECIAL, 40};
	SignatureMoves[2] = (MoveType) {{"Inferno", "Infierno"}, Fire, CAT_SPECIAL, 100};

	NormalMoves[3] = (MoveType) {{"Gust", "Rafaga"}, Flying, CAT_SPECIAL, 40};
	SignatureMoves[3] = (MoveType) {{"Razor Wind", "Viento Navaja"}, Flying, CAT_SPECIAL, 80};

	NormalMoves[4] = (MoveType) {{"Thunder Shock", "Choque de Trueno"}, Electric, CAT_SPECIAL, 40};
	SignatureMoves[4] = (MoveType) {{"Thunder", "Trueno"}, Electric, CAT_SPECIAL, 110};

	NormalMoves[5] = (MoveType) {{"Confusion", "Confusi\xA2n"}, Psychic, CAT_SPECIAL, 50};
	SignatureMoves[5] = (MoveType) {{"Hydro Pump", "Bomba de Agua"}, Water, CAT_SPECIAL, 110};

	NormalMoves[6] = (MoveType) {{"Tackle", "Entrada"}, Normal, CAT_PHYSICAL, 40};
	SignatureMoves[6] = (MoveType) {{"Fire Blast", "Expl\xA2sion de Fuego"}, Fire, CAT_SPECIAL, 110};

	NormalMoves[7] = (MoveType) {{"Wrap", "Envolver"}, Normal, CAT_PHYSICAL, 40};
	SignatureMoves[7] = (MoveType) {{"Outrage", "Atropello"}, Dragon, CAT_PHYSICAL, 120};

	NormalMoves[8] = (MoveType) {{"Pound", "Libra"}, Normal, CAT_PHYSICAL, 40};
	SignatureMoves[8] = (MoveType) {{"Double-Edge", "Doble-Filo"}, Normal, CAT_PHYSICAL, 120};

	NormalMoves[9] = (MoveType) {{"Incinerate", "Incinerar"}, Fire, CAT_SPECIAL, 60};
	SignatureMoves[9] = (MoveType) {{"Flamethrower", "Echador de Llama"}, Fire, CAT_SPECIAL, 90};

	NormalMoves[10] = (MoveType) {{"Bite", "Mordedura"}, Dark, CAT_PHYSICAL, 60};
	SignatureMoves[10] = (MoveType) {{"Take Down", "Derribar"}, Normal, CAT_PHYSICAL, 90};
	
	NormalMoves[11] = (MoveType) {{"Bubble", "Burbuja"}, Water, CAT_SPECIAL, 40};
	SignatureMoves[11] = (MoveType) {{"Dragon Pulse", "Pulso de Dragon"}, Dragon, CAT_SPECIAL, 120};
}

