
#ifndef _FIELDH_
#define _FIELDH_

#include <stdint.h>
#include "Player.h"

extern const uint8_t N; //normal
extern const uint8_t G; //grass
extern const uint8_t W; //water
extern const uint8_t fieldArray[];

typedef struct Field FieldType;

void DrawField(PlayerType player, FieldType field);

struct Field {
	const uint8_t *FieldArray;
	const uint32_t FieldWidth;
	const uint32_t FieldHeight;
};

#endif
