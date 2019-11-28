
#ifndef _FIELDH_
#define _FIELDH_

#include <stdint.h>
#include <stdbool.h>
#include "StructDec.h"

extern const uint8_t N; //normal
extern const uint8_t G; //grass
extern const uint8_t W; //water
extern const uint8_t R; //rock (cannot pass)
extern const uint8_t S; //shop (cannot pass)
extern uint8_t fieldArray[];
extern const uint8_t fieldCols;
extern const uint8_t fieldRows;


void ClearScreenGrid(void);
void InitFieldArray(void);
void InitBackgroundTypes(void);
void DrawField(PlayerType player);
bool IsWalkable(uint8_t row, uint8_t col);
uint8_t GetFieldGrid(uint8_t row, uint8_t col);
void SetFieldGrid(uint8_t row, uint8_t col, uint8_t fieldType);

#endif
