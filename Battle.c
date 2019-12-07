
#include "Battle.h"
#include "StructDec.h"
#include "ST7735.h"
#include "Draw.h"
#include "../inc/tm4c123gh6pm.h"
#include "PokemonType.h"
#include "Timer1.h"

const uint8_t CAT_PHYSICAL = 1;
const uint8_t CAT_SPECIAL = 2;

MoveType NormalMoves[20];
MoveType SignatureMoves[20];

SpriteInstType pokeShakeInst;
int8_t curX = 0;
bool timerOn = false;

void InitMoves(){
	NormalMoves[0] = (MoveType) {{"Vine Whip", "L\xA0tigo Cepa"}, Grass, CAT_PHYSICAL, 45};
	SignatureMoves[0] = (MoveType) {{"Petal Dance", "Baile P\x82talo"}, Grass, CAT_SPECIAL, 120}; //3

	NormalMoves[1] = (MoveType) {{"Water Gun", "Pistola de Agua"}, Water, CAT_SPECIAL, 40};
	SignatureMoves[1] = (MoveType) {{"Water Sprout", "Brote de Agua"}, Water, CAT_SPECIAL, 150}; //2

	NormalMoves[2] = (MoveType) {{"Ember", "Ascua"}, Fire, CAT_SPECIAL, 40};
	SignatureMoves[2] = (MoveType) {{"Inferno", "Infierno"}, Fire, CAT_SPECIAL, 100}; //4

	NormalMoves[3] = (MoveType) {{"Gust", "Rafaga"}, Flying, CAT_SPECIAL, 40};
	SignatureMoves[3] = (MoveType) {{"Razor Wind", "Viento Navaja"}, Flying, CAT_SPECIAL, 80}; //5

	NormalMoves[4] = (MoveType) {{"Thunder Shock", "Choque de Trueno"}, Electric, CAT_SPECIAL, 40};
	SignatureMoves[4] = (MoveType) {{"Thunder", "Trueno"}, Electric, CAT_SPECIAL, 110}; //4

	NormalMoves[5] = (MoveType) {{"Confusion", "Confusi\xA2n"}, Psychic, CAT_SPECIAL, 50};
	SignatureMoves[5] = (MoveType) {{"Hydro Pump", "Bomba de Agua"}, Water, CAT_SPECIAL, 110}; //3

	NormalMoves[6] = (MoveType) {{"Tackle", "Entrada"}, Normal, CAT_PHYSICAL, 40};
	SignatureMoves[6] = (MoveType) {{"Fire Blast", "Expl\xA2sion de Fuego"}, Fire, CAT_SPECIAL, 110}; //4

	NormalMoves[7] = (MoveType) {{"Wrap", "Envolver"}, Normal, CAT_PHYSICAL, 40};
	SignatureMoves[7] = (MoveType) {{"Outrage", "Atropello"}, Dragon, CAT_PHYSICAL, 120}; //3

	NormalMoves[8] = (MoveType) {{"Pound", "Libra"}, Normal, CAT_PHYSICAL, 40};
	SignatureMoves[8] = (MoveType) {{"Double-Edge", "Doble-Filo"}, Normal, CAT_PHYSICAL, 120}; //3

	NormalMoves[9] = (MoveType) {{"Incinerate", "Incinerar"}, Fire, CAT_SPECIAL, 60};
	SignatureMoves[9] = (MoveType) {{"Flamethrower", "Echador de Llama"}, Fire, CAT_SPECIAL, 90}; //5

	NormalMoves[10] = (MoveType) {{"Bite", "Mordedura"}, Dark, CAT_PHYSICAL, 60};
	SignatureMoves[10] = (MoveType) {{"Take Down", "Derribar"}, Normal, CAT_PHYSICAL, 90}; //5
	
	NormalMoves[11] = (MoveType) {{"Bubble", "Burbuja"}, Water, CAT_SPECIAL, 40};
	SignatureMoves[11] = (MoveType) {{"Dragon Pulse", "Pulso de Dragon"}, Dragon, CAT_SPECIAL, 120}; //3
	
	NormalMoves[12] = (MoveType) {{"Bone Club", "Club de Huesos"}, Ground, CAT_PHYSICAL, 65};
	SignatureMoves[12] = (MoveType) {{"Headbutt", "Cabezazo"}, Normal, CAT_PHYSICAL, 80}; //5
	
	NormalMoves[13] = (MoveType) {{"Bug Bite", "Picadura de Insecto"}, Bug, CAT_PHYSICAL, 60};
	SignatureMoves[13] = (MoveType) {{"Bug Buzz", "Zumbido de Insecto"}, Bug, CAT_SPECIAL, 90}; //5
	
	NormalMoves[14] = (MoveType) {{"Assurance", "Garantia"}, Dark, CAT_PHYSICAL, 60};
	SignatureMoves[14] = (MoveType) {{"Play Rough", "Jugar Brusco"}, Fairy, CAT_PHYSICAL, 90}; //5
	
	NormalMoves[15] = (MoveType) {{"Horn Attack", "Ataque de Cuerno"}, Normal, CAT_PHYSICAL, 65};
	SignatureMoves[15] = (MoveType) {{"Poison Jab", "Pinchazo de Veneno"}, Poison, CAT_PHYSICAL, 80}; //5
	
	NormalMoves[16] = (MoveType) {{"Headbutt", "Cabezazo"}, Normal, CAT_PHYSICAL, 70};
	SignatureMoves[16] = (MoveType) {{"Dream Eater", "Comedor de Sueños"}, Psychic, CAT_SPECIAL, 100}; //4
	
	NormalMoves[17] = (MoveType) {{"Lick", "Lamer"}, Ghost, CAT_PHYSICAL, 30};
	SignatureMoves[17] = (MoveType) {{"Dark Pulse", "Pulso Oscuro"}, Dark, CAT_SPECIAL, 80};
	
	NormalMoves[18] = (MoveType) {{"Low Sweep", "Barrido Bajo"}, Fighting, CAT_PHYSICAL, 60};
	SignatureMoves[18] = (MoveType) {{"Cross Chop", "Corte Cruzado"}, Fighting, CAT_PHYSICAL, 100};
	
	NormalMoves[19] = (MoveType) {{"Rock Throw", "Lanzamiento de Roca"}, Rock, CAT_PHYSICAL, 50};
	SignatureMoves[19] = (MoveType) {{"Earthquake", "Terremoto"}, Ground, CAT_PHYSICAL, 100};
	
}

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

void DrawDamageShake(){
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
}
