
#ifndef _SPACEINVADERSH_
#define _SPACEINVADERSH_

#include "StructDec.h"
#include <stdbool.h>

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
void PrintWinLoseScreen(bool win);

#endif
