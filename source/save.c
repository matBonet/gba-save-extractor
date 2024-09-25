#include "base_include.h"
#include "save.h"
#include <stdio.h>
#include <stddef.h>

#define SAVE_POS  0x0E000000   // Save memory base address (SRAM/Flash)
#define SAVE_SIZE 0x00010000   // Maximum size of the save data (64KB)
#define EWRAM_POS 0x0202FFFF   // Base address of EWRAM to store save data, starting from the end

void display_progress(unsigned int current, unsigned int max) {
    float percentage = (float)current / (float)max;
    int full_chars = (int)(percentage * 10);
    printf("\x1b[9;5H"); // Move cursor to the desired position
    printf("["); // Start the progress bar
    for (int i = 0; i < 10; i++) {
        (i < full_chars) ? printf("x"): printf(" ");
    }
    printf("]  %.2f%%\n", percentage * 100); // Display percentage
}

void copy_save_to_ewram() {
    unsigned char curr_save_data;

    for (u16 i = 0; i < SAVE_SIZE; i++) {
        // Use bytewise access for SRAM
        volatile unsigned char *sram_pointer = (volatile unsigned char *)(SAVE_POS + i);
        volatile unsigned char *ewram_ptr = (volatile unsigned char *)(EWRAM_POS + i);
        unsigned char curr_save_data = *sram_pointer; // Read from SRAM
        *ewram_ptr = curr_save_data; // Copy to EWRAM
        
        if (!(i % 1000)) {display_progress(i, SAVE_SIZE);}
        if (i==SAVE_SIZE-1){break;}
    }
}

void copy_ewram_to_save() {
    return;
}