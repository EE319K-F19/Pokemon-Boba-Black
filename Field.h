
#ifndef _FIELDH_
#define _FIELDH_

#include <stdint.h>
#include "Player.h"

extern const uint8_t N; //normal
extern const uint8_t G; //grass
extern const uint8_t W; //water

typedef struct Field FieldType;

void DrawField(PlayerType player, FieldType field);
uint32_t GetMidGrid(void);
struct Field {
	const uint8_t *FieldArray;
	const uint32_t FieldWidth;
	const uint32_t FieldHeight;
	uint32_t XPos;
	uint32_t YPos;
};

extern const uint8_t fieldArray[];

#endif
