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
void Sound_Attack1(void);
void Sound_Attack2(void);
void Sound_Heal(void);
int sound_main(void);

extern const uint8_t Attack_Heal_Drain[];
extern const uint8_t Mega_Punch[];
extern const uint8_t Secret_Sword[];
extern const uint8_t highpitch[];

extern const uint8_t* soundPt;
extern uint32_t len;
extern uint32_t soundStatus;


