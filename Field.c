
#include <stdint.h>
#include "ST7735.h"
#include "Field.h"
#include "SystemInfo.h"
#include "Draw.h"

const uint8_t N = 0;
const uint8_t G = 1;
const uint8_t W = 2;
const uint8_t R = 3;
const uint8_t fieldCols = 64;
const uint8_t fieldRows = 40;

void InitFieldArray(){
	for(int i=0; i<fieldRows; i++){
		for(int j=0; j<fieldCols; j++){
			if(i==SCREEN_MID_ROW || j==SCREEN_MID_COL || i==fieldRows-SCREEN_MID_ROW-1 || j==fieldCols-SCREEN_MID_ROW-1){
				SetFieldGrid(i, j, R);
			}
		}
	}
}

void DrawField(PlayerType player, FieldType field){
	
	for(int i=0; i<SCREEN_ROWS; i++){
		for(int j=0; j<SCREEN_COLUMNS; j++){
			uint8_t screenCol = j + player.XPos - SCREEN_MID_COL;
			uint8_t screenRow = i + player.YPos - SCREEN_MID_ROW;
			if(player.XPos == screenCol && player.YPos == screenRow){
				DrawGridSprite(j, i, *player.sprite);
				continue;
			}
			uint8_t fieldType = field.FieldArray[screenRow*field.FieldWidth+screenCol];
			uint16_t fieldColor = ST7735_WHITE;
			if(fieldType == N) fieldColor = 0x4A5A;
			else if(fieldType == W) fieldColor = 0xEFC7;
			else if(fieldType == G) fieldColor = 0x9F8F;
			else if(fieldType == R) fieldColor = 0x0000;
			DrawGridFill(j, i, fieldColor);
			
		}
	}
}

uint8_t IsWalkable(uint8_t row, uint8_t col){
	if(GetFieldGrid(row, col) != R) return 1;
	return 0;
}

uint8_t GetFieldGrid(uint8_t row, uint8_t col){
	return fieldArray[row*fieldCols + col];
}

void SetFieldGrid(uint8_t row, uint8_t col, uint8_t fieldType){
	fieldArray[row*fieldCols + col] = fieldType;
}

uint8_t fieldArray[] = {
//0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63
	N, W, W, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, //0
	N, W, W, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, W, W, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, //1
	N, W, W, W, W, W, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, W, N, N, W, W, N, N, N, N, N, N, N, N, G, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, //2
	N, G, W, W, W, W, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, W, N, W, W, W, W, N, N, N, N, N, N, N, G, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, //3
	N, G, G, W, W, W, W, W, N, N, N, N, N, N, N, N, N, N, N, N, W, W, W, W, N, W, W, W, N, N, N, N, N, N, N, G, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, //4
	N, G, G, N, W, W, W, N, N, N, N, N, N, N, N, N, N, N, N, N, W, W, W, W, W, W, W, W, N, N, N, N, N, G, G, G, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, //5
	N, G, N, N, W, W, W, N, N, N, N, N, N, N, N, N, N, N, N, W, W, W, N, G, W, N, N, N, N, N, N, N, N, G, G, G, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, //6
	G, G, G, N, W, W, N, N, N, N, N, N, N, N, N, N, N, N, N, W, W, N, N, G, W, W, W, G, N, N, N, N, G, G, G, G, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, //7
	G, G, G, N, W, W, N, N, N, N, N, N, N, N, N, N, N, N, N, W, W, N, N, N, W, W, W, G, N, N, N, N, G, G, G, G, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, //8
	N, G, G, N, W, W, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, W, W, W, G, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, //9
	N, G, G, G, W, W, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, G, G, G, G, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, //10
	N, G, G, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, G, G, G, G, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, //11
	N, G, G, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, G, G, G, G, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, //12
	N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, G, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, //13
	N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, G, G, G, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, //14
	N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, G, G, G, G, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, //15
	N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, W, G, G, G, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, //16
	N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, W, W, W, W, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, //17
	N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, W, W, W, W, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, //18
	N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, W, W, W, W, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, //19
	N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, W, W, W, W, G, G, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, //20
	N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, W, W, W, G, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, //21
	N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, W, W, W, G, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, //22
	N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, W, W, W, G, G, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, //23
	N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, W, N, G, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, //24
	N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, W, G, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, //25
	N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, G, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, //26
	N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, //27
	N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, //28
	N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, //29
	N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, //30
	N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, //31
	N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, //32
	N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, //33
	N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, //34
	N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, //35
	N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, //36
	N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, //37
	N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, //38
	N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, //39
};
