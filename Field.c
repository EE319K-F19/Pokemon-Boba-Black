
#include <stdint.h>
#include "Draw.h"
#include "Field.h"
#include "ImagesOther.h"
#include "Player.h"
#include "SystemInfo.h"

//field types
const uint8_t N = 0;
const uint8_t G = 1;
const uint8_t W = 2;
const uint8_t E = 3;

//field objects
const uint8_t R = 4;
const uint8_t T = 5;
const uint8_t S = 6;

const uint8_t FIELD_WIDTH = 30;
const uint8_t FIELD_HEIGHT = 30;

SpriteType background[3];
SpriteType fieldObj[3];
uint8_t screenGrid[63];
uint8_t screenObj[63];

void ClearScreenGrid(){
	for(int i=0; i<63; i++){
		screenGrid[i] = E;
		screenObj[i] = E;
	}
}

void InitFieldArray(){
}

void InitBackgroundTypes(){
	background[0] = (SpriteType) {ground, 16, 16};
	background[1] = (SpriteType) {grass, 16, 16};
	background[2] = (SpriteType) {water, 16, 16};
	
	fieldObj[0] = (SpriteType) {rock, 16, 16};
	fieldObj[1] = (SpriteType) {bush, 16, 16};
}

void DrawField(){
	DrawBorder(GAME_BORDER_W, GAME_BORDER_W, _width-2*GAME_BORDER_W, _height-2*GAME_BORDER_W, GAME_BORDER_W, GAME_BORDER_COLOR);
	
	fieldObj[2] = (SpriteType) {p1.sprite.image, 16, 16};
	
	for(int i=0; i<SCREEN_ROWS; i++){
		for(int j=0; j<SCREEN_COLUMNS; j++){
			uint8_t screenCol = j + p1.XPos - SCREEN_MID_COL;
			uint8_t screenRow = i + p1.YPos - SCREEN_MID_ROW;
			uint8_t fieldType = fieldArray[screenRow*FIELD_WIDTH+screenCol];
			uint8_t objType = fieldObjArray[screenRow*FIELD_WIDTH+screenCol];
			
			if(objType == R || objType == T || (p1.XPos == screenCol && p1.YPos == screenRow)){
				
				if(p1.XPos == screenCol && p1.YPos == screenRow) objType = 2;
				else objType -= 4;
				uint16_t combinedSprite[16*16];
				for(int i=0; i<16*16; i++){
					if(fieldObj[objType].image[i] == 0xFFFF){
						combinedSprite[i] = background[fieldType].image[i];
					}else {
						combinedSprite[i] = fieldObj[objType].image[i];
					}
				}
				SpriteType combined = {combinedSprite, 16, 16};
				DrawGridSprite(j, i, combined);
			}else if(screenGrid[i*SCREEN_COLUMNS+j] != fieldType || (screenObj[i*SCREEN_COLUMNS+j] != R && screenObj[i*SCREEN_COLUMNS+j] != T)){
				DrawGridSprite(j, i, background[fieldType]);
			}
			screenGrid[i*SCREEN_COLUMNS+j] = fieldType;
			screenObj[i*SCREEN_COLUMNS+j] = objType;
		}
	}
}

bool IsWalkable(uint8_t row, uint8_t col){
	return GetObjGrid(row, col) != R && GetObjGrid(row, col) != T;
}

uint8_t GetFieldGrid(uint8_t row, uint8_t col){
	return fieldArray[row*FIELD_WIDTH + col];
}

uint8_t GetObjGrid(uint8_t row, uint8_t col){
	return fieldObjArray[row*FIELD_WIDTH + col];
}

void SetFieldGrid(uint8_t row, uint8_t col, uint8_t fieldType){
	fieldArray[row*FIELD_WIDTH + col] = fieldType;
}

uint8_t fieldArray[] = {
//0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,
	N, W, W, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, //0
	N, W, W, W, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, W, W, N, N, N, //1
	N, W, W, W, W, W, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, W, N, N, W, W, N, N, N, //2
	N, G, W, W, W, W, W, N, N, N, N, N, G, N, N, N, N, N, N, N, N, W, W, N, W, W, W, W, N, N, //3
	N, G, G, G, W, W, W, N, N, N, W, N, G, G, N, N, N, N, N, N, N, W, W, W, N, W, W, W, N, N, //4
	N, G, G, G, W, W, W, N, N, N, W, N, G, G, G, N, N, N, N, N, W, W, W, W, W, W, W, W, N, N, //5
	N, G, G, G, W, W, W, N, N, W, W, G, G, G, G, N, N, N, N, W, W, W, N, N, W, N, N, N, N, N, //6
	G, G, G, G, W, W, W, N, W, W, W, G, G, N, G, N, N, N, N, W, W, N, N, N, W, W, W, G, N, N, //7
	G, G, G, G, G, W, W, W, W, W, W, W, W, W, N, N, N, N, N, W, W, N, N, N, N, N, N, G, N, N, //8
	N, G, G, G, G, G, N, W, W, W, W, W, G, W, N, N, N, N, N, N, N, N, N, N, W, W, G, G, N, N, //9
	N, G, G, N, G, G, N, N, W, W, G, G, G, W, W, N, N, N, N, N, N, N, N, N, N, N, G, G, G, G, //10
	N, G, G, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, G, G, G, G, //11
	N, G, G, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, W, W, N, N, N, N, N, G, G, G, G, G, //12
	N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, W, W, N, N, N, N, N, N, N, N, G, N, //13
	N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, G, W, G, N, N, N, N, N, N, N, N, N, N, //14
	N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, G, G, G, G, N, N, N, N, N, N, N, N, N, N, //15
	N, N, G, G, G, N, N, N, N, N, N, N, N, N, N, N, G, G, G, G, N, N, N, N, N, W, W, W, N, N, //16
	N, N, G, G, G, N, N, N, N, N, G, G, N, N, N, G, G, W, W, W, N, N, N, N, N, N, W, W, N, N, //17
	N, N, G, N, G, G, G, W, W, N, G, G, N, N, N, G, G, W, W, W, W, W, N, W, N, N, W, W, N, N, //18
	N, N, N, N, G, G, G, W, W, G, G, G, N, N, N, G, W, W, W, W, W, W, W, W, W, N, N, N, N, N, //19
	N, N, N, N, N, N, G, W, W, N, G, G, G, N, N, N, N, N, N, N, N, W, W, N, W, W, N, N, G, N, //20
	N, N, N, N, N, G, G, G, N, N, N, W, G, N, N, N, N, G, N, G, N, N, N, N, N, G, G, G, G, N, //21
	N, N, N, N, N, G, G, N, N, N, N, W, G, N, N, N, N, N, N, G, N, N, N, N, G, G, G, G, N, N, //22
	N, N, N, N, N, N, N, N, N, N, W, W, G, W, W, N, W, G, G, G, N, N, N, N, G, G, G, G, N, N, //23
	N, N, N, N, N, N, N, N, N, N, W, W, W, W, W, N, W, W, W, W, N, N, N, N, N, G, G, G, N, N, //24
	N, N, N, N, N, N, N, N, N, N, W, W, W, N, W, W, W, W, W, W, N, N, N, N, N, N, N, N, N, N, //25
	N, N, N, N, N, N, N, N, N, N, N, N, N, N, W, W, W, W, W, W, W, W, W, W, W, N, N, N, N, N, //26
	N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, W, W, W, W, W, W, W, W, W, W, N, N, N, N, N, //27
	N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, W, W, W, W, N, W, W, W, N, N, N, N, N, N, //28
	N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, W, W, W, W, N, N, N, N, N, N, N, N, N, N, //29
};

uint8_t fieldObjArray[] = {
//0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,
	T, W, W, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, //0
	T, W, W, W, T, T, T, N, T, T, T, N, T, N, T, N, T, N, T, N, T, T, T, T, T, R, R, T, T, T, //1
	T, W, R, W, W, W, T, T, T, T, N, T, N, T, N, T, N, T, N, N, T, T, T, T, T, W, W, T, T, T, //2
	T, T, R, R, R, R, R, T, T, T, T, T, T, T, T, T, T, T, T, T, T, R, R, T, R, R, R, R, T, T, //3
	T, T, T, G, W, W, W, N, N, N, W, N, G, G, N, N, N, N, N, N, N, W, W, W, N, W, W, R, R, R, //4
	T, T, T, G, W, W, W, N, N, N, W, N, G, G, G, N, N, N, N, N, W, W, W, W, W, W, W, R, R, R, //5
	T, T, T, G, W, W, W, N, N, W, W, G, G, G, G, N, N, N, N, W, W, W, N, N, W, N, N, T, R, R, //6
	T, T, T, G, W, W, W, N, W, W, W, G, G, N, G, N, N, N, N, W, W, N, N, N, W, W, W, T, R, R, //7
	T, T, T, G, G, W, W, W, W, W, W, W, W, W, N, N, N, N, N, W, W, N, N, N, N, N, N, T, R, R, //8
	T, T, T, G, G, G, N, W, W, W, W, W, G, W, N, N, N, N, N, N, N, N, N, N, W, W, G, R, T, R, //9
	T, T, T, N, G, G, N, N, W, W, G, G, G, W, W, N, N, N, N, N, N, N, N, N, N, N, G, T, T, T, //10
	T, T, T, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, G, T, T, T, //11
	T, T, T, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, W, W, N, N, N, N, N, G, G, T, T, T, //12
	T, T, T, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, W, W, N, N, N, N, N, N, N, T, T, T, //13
	T, T, T, N, N, N, N, N, N, N, N, N, N, N, N, N, N, G, W, G, N, N, N, N, N, N, N, T, T, T, //14
	T, T, T, N, N, N, N, N, N, N, N, N, N, N, N, N, G, G, G, G, N, N, N, N, N, N, N, T, T, T, //15
	T, T, T, G, G, N, N, N, N, N, N, N, N, N, N, N, G, G, G, G, N, N, N, N, N, W, W, T, T, T, //16
	T, T, T, G, G, N, N, N, N, N, G, G, N, N, N, G, G, W, W, W, N, N, N, N, N, N, W, T, T, T, //17
	T, T, T, N, G, G, G, W, W, N, G, G, N, N, N, G, G, W, W, W, W, W, N, W, N, N, W, T, T, T, //18
	T, T, T, N, G, G, G, W, W, G, G, G, N, N, N, G, W, W, W, W, W, W, W, W, W, N, N, T, T, T, //19
	T, T, T, N, N, N, G, W, W, N, G, G, G, N, N, N, N, N, N, N, N, W, W, N, W, W, N, T, T, T, //20
	T, T, T, N, N, G, G, G, N, N, N, W, G, N, N, N, N, G, N, G, N, N, N, N, N, G, G, T, T, T, //21
	T, T, T, N, N, G, G, N, N, N, N, W, G, N, N, N, N, N, N, G, N, N, N, N, G, G, G, T, T, T, //22
	T, T, T, N, N, N, N, N, N, N, W, W, G, W, W, N, W, G, G, G, N, N, N, N, G, G, G, T, T, T, //23
	T, T, T, N, N, N, N, N, N, N, W, W, W, W, W, N, W, W, W, W, N, N, N, N, N, G, G, T, T, T, //24
	T, T, T, N, N, N, N, N, N, N, W, W, W, N, W, W, W, W, W, W, N, N, N, N, N, N, N, T, T, T, //25
	T, T, T, T, T, T, T, T, T, T, T, T, T, R, R, R, R, R, R, R, R, R, R, R, R, R, R, T, T, T, //26
	T, T, T, T, T, T, T, T, T, T, T, T, T, T, R, R, R, R, W, R, R, R, R, R, R, N, R, T, T, T, //27
	T, T, T, T, T, T, T, T, T, T, T, T, T, T, R, R, R, W, W, W, N, W, W, W, N, N, N, T, T, T, //28
	T, T, T, T, T, T, T, T, T, T, T, T, T, T, R, R, W, W, W, W, N, N, N, N, N, N, N, T, T, T, //29
};
