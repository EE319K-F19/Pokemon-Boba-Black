
#include <stdint.h>
#include <stdbool.h>
#include "StructDec.h"

extern const uint8_t CAT_PHYSICAL;
extern const uint8_t CAT_SPECIAL;

extern MoveType NormalMoves[20];
extern MoveType SignatureMoves[20];

extern SpriteInstType pokeShakeInst;

void InitMoves(void);
void DrawDamageShake(void);
