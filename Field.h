
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
extern uint8_t fieldObjArray[];

extern GridCoordinateType grassGrids[900];
extern uint32_t grassGridsLength;
extern GridCoordinateType waterGrids[900];
extern uint32_t waterGridsLength;

extern const uint8_t grassTile;
extern const uint8_t waterTile;
extern const uint8_t bothTile;

extern PokemonInstType WorldPokemons[20];
extern uint8_t numWorldPokemon;
extern uint8_t numWorldInstantiated;
extern const uint8_t FIELD_WIDTH;
extern const uint8_t FIELD_HEIGHT;

void InitGridCoordinates(void);
void ClearScreenGrid(void);
void InitFieldArray(void);
void InitBackgroundTypes(void);
void DrawField(void);
bool IsWalkable(uint8_t row, uint8_t col);
bool IsPokemonWalkable(uint8_t row, uint8_t col, uint8_t preRow, uint8_t preCol, uint8_t index);
uint8_t GetFieldGrid(uint8_t row, uint8_t col);
uint8_t GetObjGrid(uint8_t row, uint8_t col);
void SetFieldGrid(uint8_t row, uint8_t col, uint8_t fieldType);
int8_t BumpedIntoWorldPokemon(void);
bool IsGridObject(uint8_t objType);
int8_t IsWorldPokemon(uint8_t row, uint8_t col);

#endif
