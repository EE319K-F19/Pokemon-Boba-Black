
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

TypeType Typings[] = {
	// NorFirWatEleGraIceFigPoiGroFlyPsyBugRocGhoDraDarSteFai
		{B,	B, B, B, B, B, B, B, B, B, B, B, C, D, B, B, C, B}, //Normal
		{B, C, C, B, A, A, B, B, B, B, B, A, C, B, C, B, A, B}, //Fire
		{B, A, C, B, C, B, B, B, A, B, B, B, A, B, C, B, B, B}, //Water
		{B, B, A, C, C, B, B, B, D, A, B, B, B, B, C, B, B, B}, //Electric
		{B, C, A, B, C, B, B, C, A, C, B, C, A, B, C, B, C, B}, //Grass
		{B, C, C, B, A, C, B, B, A, A, B, B, B, B, A, B, C, B}, //Ice
		{A, B, B, B, B, A, B, C, A, C, C, C, A, D, B, A, A, C}, //Fighting
		{B, B, B, B, A, B, B, C, C, B, B, B, C, C, B, B, D, A}, //Poison
		{B, A, B, A, C, B, B, A, B, D, B, C, A, B, B, B, A, B}, //Ground
		{B, B, B, C, A, B, A, B, B, B, B, A, C, B, B, B, C, B}, //Flying
		{B, B, B, B, B, B, A, A, B, B, C, B, B, B, B, D, C, B}, //Psychic
		{B, C, B, B, A, B, C, C, B, C, A, B, B, C, B, A, C, C}, //Bug
		{B, A, B, B, B, A, C, B, C, A, B, A, B, B, B, B, C, B}, //Rock
		{D, B, B, B, B, B, B, B, B, B, A, B, B, A, B, C, B, B}, //Ghost
		{B, B, B, B, B, B, B, B, B, B, B, B, B, B, A, B, C, D}, //Dragon
		{B, B, B, B, B, B, C, B, B, B, A, B, B, A, B, C, B, C}, //Dark
		{B, C, C, C, B, A, B, B, B, B, B, B, A, B, B, B, C, A}, //Steel
		{B, C, B, B, B, B, A, C, B, B, B, B, B, B, A, A, C, B},  //Fairy
};
