#ifndef BASE_INCLUDE__
#define BASE_INCLUDE__

#ifdef __GBA__

#include <gba.h>
#define ROM 0x8000000
#define REG_WAITCNT *(vu16*)(REG_BASE + 0x204) // Wait state Control
#define SRAM_READING_VALID_WAITCYCLES 3
#define NON_SRAM_MASK 0xFFFC
#define CLOCK_SPEED 16777216
#endif

#endif