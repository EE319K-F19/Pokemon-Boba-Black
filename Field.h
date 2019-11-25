
#ifndef _FIELDH_
#define _FIELDH_

#include <stdint.h>
#include "Player.h"

extern const uint8_t N; //normal
extern const uint8_t G; //grass
extern const uint8_t W; //water
extern const uint8_t R; //rock (cannot pass)
extern uint8_t fieldArray[];
extern const uint8_t fieldCols;
extern const uint8_t fieldRows;

typedef struct Field FieldType;

struct Field {
	uint8_t *FieldArray;
	const uint32_t FieldWidth;
	const uint32_t FieldHeight;
};

void InitFieldArray(void);
void DrawField(PlayerType player, FieldType field);
uint8_t GetFieldGrid(uint8_t row, uint8_t col);
void SetFieldGrid(uint8_t row, uint8_t col, uint8_t fieldType);

#endif
