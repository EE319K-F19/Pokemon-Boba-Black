
#ifndef POKEMONTYPEH
#define POKEMONTYPEH

#include <stdint.h>
#include "StructDec.h"

extern const uint8_t Normal; 
extern const uint8_t Fire; 
extern const uint8_t Water;
extern const uint8_t Electric;
extern const uint8_t Grass;
extern const uint8_t Ice;
extern const uint8_t Fighting;
extern const uint8_t Poison;
extern const uint8_t Ground;
extern const uint8_t Flying;
extern const uint8_t Psychic;
extern const uint8_t Bug;
extern const uint8_t Rock;
extern const uint8_t Ghost;
extern const uint8_t Dragon;
extern const uint8_t Dark;
extern const uint8_t Steel;
extern const uint8_t Fairy;

extern const uint8_t A; //Very Effective
extern const uint8_t B; //Normal effectiveness
extern const uint8_t C; //Not very effective
extern const uint8_t D; //No Effect


extern TypeType TypesArray[18];
void InitTyping(void);

#endif
