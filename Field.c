
#include <stdint.h>
#include "Draw.h"
#include "Field.h"
#include "ImagesOther.h"
#include "Player.h"
#include "SystemInfo.h"

const uint8_t N = 0;
const uint8_t G = 1;
const uint8_t W = 2;
const uint8_t R = 3;
const uint8_t E = 4;
const uint8_t S = 5;
const uint8_t fieldCols = 30;
const uint8_t fieldRows = 20;
const uint8_t FIELD_WIDTH = 30;
const uint8_t FIELD_HEIGHT = 20;

SpriteType background[4]; 

uint8_t screenGrid[63];

void ClearScreenGrid(){
	for(int i=0; i<63; i++){
		screenGrid[i] = E;
	}
}

void InitFieldArray(){
}

void InitBackgroundTypes(){
	background[0] = (SpriteType) {ground, 16, 16};
	background[1] = (SpriteType) {grass, 16, 16};
	background[2] = (SpriteType) {water, 16, 16};
	background[3] = (SpriteType) {rock, 16, 16};
}

void DrawField(){
	DrawBorder(GAME_BORDER_W, GAME_BORDER_W, _width-2*GAME_BORDER_W, _height-2*GAME_BORDER_W, GAME_BORDER_W, GAME_BORDER_COLOR);
	for(int i=0; i<SCREEN_ROWS; i++){
		for(int j=0; j<SCREEN_COLUMNS; j++){
			uint8_t screenCol = j + p1.XPos - SCREEN_MID_COL;
			uint8_t screenRow = i + p1.YPos - SCREEN_MID_ROW;
			uint8_t fieldType = fieldArray[screenRow*FIELD_WIDTH+screenCol];
			
			if(p1.XPos == screenCol && p1.YPos == screenRow){
				uint16_t combinedSprite[16*16];
				for(int i=0; i<16*16; i++){
					if(p1.sprite.image[i] == 0xFFFF){
						combinedSprite[i] = background[fieldType].image[i];
					}else {
						combinedSprite[i] = p1.sprite.image[i];
					}
				}
				SpriteType combined = {combinedSprite, 16, 16};
				DrawGridSprite(j, i, combined);
			}else if(fieldType == S){
				uint16_t combinedSprite[16*16];
				for(int i=0; i<16*16; i++){
					if(p1.spriteFront.image[i] == 0xFFFF){
						combinedSprite[i] = background[N].image[i];
					}else {
						combinedSprite[i] = p1.spriteFront.image[i];
					}
				}
				SpriteType combined = {combinedSprite, 16, 16};
				DrawGridSprite(j, i, combined);
			}else if(screenGrid[i*SCREEN_COLUMNS+j] != fieldType){
				DrawGridSprite(j, i, background[fieldType]);
			}
			screenGrid[i*SCREEN_COLUMNS+j] = fieldType;
		}
	}
}

bool IsWalkable(uint8_t row, uint8_t col){
	return GetFieldGrid(row, col) != R && GetFieldGrid(row, col) != S;
}

uint8_t GetFieldGrid(uint8_t row, uint8_t col){
	return fieldArray[row*fieldCols + col];
}

void SetFieldGrid(uint8_t row, uint8_t col, uint8_t fieldType){
	fieldArray[row*fieldCols + col] = fieldType;
}

uint8_t fieldArray[] = {
//0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,
	N, W, W, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, //0
	N, W, W, W, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, W, W, N, N, N, //1
	N, W, W, W, W, W, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, W, R, N, W, W, N, N, N, //2
	N, G, W, W, W, W, N, N, R, N, N, N, G, N, N, N, N, N, N, R, N, N, R, R, W, W, W, W, N, N, //3
	N, G, G, R, W, W, R, R, R, R, N, N, G, G, R, R, N, N, R, R, R, R, R, R, N, W, W, W, N, N, //4
	N, G, G, R, R, R, R, N, N, R, R, R, R, R, R, R, R, R, R, R, W, W, W, R, W, W, W, W, N, N, //5
	N, G, N, N, R, W, W, N, N, R, R, G, G, G, G, N, N, N, N, W, W, W, N, R, W, N, N, N, N, N, //6
	G, G, G, N, R, W, N, N, N, W, W, G, G, N, N, N, N, N, N, W, W, N, N, R, W, W, W, G, N, N, //7
	G, G, G, N, R, W, N, N, N, W, W, W, G, N, N, S, N, N, N, W, W, N, N, N, R, R, R, G, N, N, //8
	N, G, G, R, R, W, N, N, N, W, W, W, G, N, N, N, N, N, N, N, N, N, N, N, W, W, R, R, N, N, //9
	N, G, G, R, R, W, N, N, N, N, G, G, G, N, N, N, N, N, N, N, N, N, N, N, N, N, R, R, G, G, //10
	N, G, G, R, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, R, R, G, G, //11
	N, G, G, R, R, N, R, R, N, N, R, R, N, N, N, N, N, N, N, N, R, N, N, N, N, N, R, R, G, G, //12
	N, N, N, R, R, N, R, R, N, N, R, N, R, N, N, N, N, N, N, R, N, R, N, N, N, N, R, R, G, N, //13
	N, N, N, N, R, N, R, R, R, R, R, N, R, R, R, R, N, G, R, G, N, R, N, N, N, N, R, R, N, N, //14
	N, N, N, N, R, R, R, N, N, N, N, N, N, N, N, R, R, R, R, G, N, R, R, R, R, R, R, R, N, N, //15
	N, N, N, N, R, N, N, N, N, N, N, N, N, N, N, N, W, G, G, G, N, R, N, N, N, N, N, N, N, N, //16
	N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, W, W, W, W, N, N, N, N, N, N, N, N, N, N, //17
	N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, W, W, W, W, N, N, N, N, N, N, N, N, N, N, //18
	N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, W, W, W, W, N, N, N, N, N, N, N, N, N, N, //19
};
