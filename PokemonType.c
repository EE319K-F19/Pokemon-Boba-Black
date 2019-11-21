
#include <stdint.h>
#include "PokemonType.h"

const uint8_t Normal = 0; 
const uint8_t Fire = 1; 
const uint8_t Water = 2;
const uint8_t Electric = 3;
const uint8_t Grass = 4;
const uint8_t Ice = 5;
const uint8_t Fighting = 6;
const uint8_t Poison = 7;
const uint8_t Ground = 8;
const uint8_t Flying = 9;
const uint8_t Psychic = 10;
const uint8_t Bug = 11;
const uint8_t Rock = 12;
const uint8_t Ghost = 13;
const uint8_t Dragon = 14;
const uint8_t Dark = 15;
const uint8_t Steel = 16;
const uint8_t Fairy = 17;

const uint8_t A = 4; //Very Effective
const uint8_t B = 2; //Normal effectiveness
const uint8_t C = 1; //Not very effective
const uint8_t D = 0; //No Effect

TypingType Typings[] = {
	// NorFirWatEleGraIceFigPoiGroFlyPsyBugRocGhoDraDarSteFai
		{B,	B, B, B, B, B, B, B, B, B, B, B, C, D, B, B, C, B}, //Normal
		{B, C, C, B, A, A, B, B, B, B, B, A, C, B, C, B, A, B}, //Fire
		{B, A, C, B, C, B, B, B, A, B, B, B, A, B, C, B, B, B}, //Water
		{B, B, A, C, C, B, B, B, D, A, B, B, B, B, B, B, B, B}, //Electric
		{B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B}, //Grass
		{B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B}, //Ice
		{B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B}, //Fighting
		{B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B}, //Poison
		{B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B}, //Ground
		{B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B}, //Flying
		{B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B}, //Psychic
		{B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B}, //Bug
		{B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B}, //Rock
		{B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B}, //Ghost
		{B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B}, //Dragon
		{B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B}, //Dark
		{B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B}, //Steel
		{B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B},  //Fairy
};














