// Sound.h
// Runs on TM4C123 or LM4F120
// Prototypes for basic functions to play sounds from the
// original Space Invaders.
// Jonathan Valvano
// November 17, 2014

#include <stdint.h>
void Sound_Init(void);
void Sound_Task(void);
void Sound_Play(const uint8_t *pt, uint32_t count);
void Sound_Highpitch(void);
void Sound_Alarm(void);
int sound_main(void);

extern const uint8_t highpitch[];
extern const uint8_t alarm[];
extern const uint8_t buzz[];
extern const uint8_t laser[];
extern const uint8_t rumble[];
extern const uint8_t stomp[];

extern const uint8_t* soundPt;
extern uint32_t len;


