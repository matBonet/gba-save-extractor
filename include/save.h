#ifndef SAVE__
#define SAVE__

#include <stddef.h>

void copy_save_to_ram(uintptr_t, u8*, size_t);
void init_bank(void);

#endif
