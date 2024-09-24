#ifndef DELAYS__
#define DELAYS__

#define CLOCK_CYCLES_PER_MS(x) ((((x) * ((uint64_t)CLOCK_SPEED)) + 999) / 1000)

void delay_cycles(u32);

#endif
