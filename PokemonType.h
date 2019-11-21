
#include <stdint.h>

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

typedef struct Typing TypingType;

struct Typing {
	const uint8_t Normal; 
	const uint8_t Fire; 
	const uint8_t Water;
	const uint8_t Electric;
	const uint8_t Grass;
	const uint8_t Ice;
	const uint8_t Fighting;
	const uint8_t Poison;
	const uint8_t Ground;
	const uint8_t Flying;
	const uint8_t Psychic;
	const uint8_t Bug;
	const uint8_t Rock;
	const uint8_t Ghost;
	const uint8_t Dragon;
	const uint8_t Dark;
	const uint8_t Steel;
	const uint8_t Fairy;
};

void InitTyping(void);
extern TypingType Typings[18];
