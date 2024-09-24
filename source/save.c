#include "base_include.h"
#include "save.h"
#include <stddef.h>
#include "delays.h"

#define IS_FLASH 1
#define SAVE_POS SRAM

#define BASE_FLASH_CMD *((vu8*)(SAVE_POS+0x5555)) = 0xAA; *((vu8*)(SAVE_POS+0x2AAA)) = 0x55;
#define FLASH_BANK_CMD BASE_FLASH_CMD *((vu8*)(SAVE_POS+0x5555)) = 0xB0;
#define FLASH_TERM_CMD *((vu8*)(SAVE_POS+0x5555)) = 0xF0;
#define FLASH_ENTER_MAN_CMD BASE_FLASH_CMD *((vu8*)(SAVE_POS+0x5555)) = 0x90;
#define FLASH_EXIT_MAN_CMD BASE_FLASH_CMD FLASH_TERM_CMD FLASH_TERM_CMD
#define ID_TIMEOUT_CYCLES CLOCK_CYCLES_PER_MS(28)

#define BANK_SIZE 0x10000
#define NUM_BANKS 2

#define MACRONIX_MAN_ID 0xC2
#define SANYO_MAN_ID 0x62
#define DEFAULT_MAN_ID 0

#if IS_FLASH
#define BANK_LIMIT BANK_SIZE
#else
#define BANK_LIMIT (NUM_BANKS * BANK_SIZE)
#endif

static uintptr_t bank_check(uintptr_t);
static size_t sanitize_save_size(uintptr_t, size_t);
static u8 read_direct_single_byte_save(uintptr_t);

u8 current_bank;
u8 is_macronix;

IWRAM_CODE void init_bank() {
    REG_WAITCNT &= NON_SRAM_MASK;
    REG_WAITCNT |= SRAM_READING_VALID_WAITCYCLES;
    current_bank = NUM_BANKS;
    is_macronix = 0;
    #if IS_FLASH
    FLASH_ENTER_MAN_CMD
    delay_cycles(ID_TIMEOUT_CYCLES);
    u8 man_id = *((vu8*)SAVE_POS);
    if((man_id == MACRONIX_MAN_ID) || (man_id == SANYO_MAN_ID) || (man_id == DEFAULT_MAN_ID))
        is_macronix = 1;
    FLASH_EXIT_MAN_CMD
    delay_cycles(ID_TIMEOUT_CYCLES);
    #endif
}

IWRAM_CODE uintptr_t bank_check(uintptr_t address) {
    address %= (NUM_BANKS * BANK_SIZE);
    #if IS_FLASH
    u8 bank = address / BANK_SIZE;
    address %= BANK_SIZE;

    if(bank != current_bank) {
        FLASH_BANK_CMD
        *((vu8*)SAVE_POS) = bank;
        current_bank = bank;
    }
    #endif
    return address;
}

IWRAM_CODE u8 read_direct_single_byte_save(uintptr_t address) {
    return *(vu8*)(SAVE_POS + address);
}

IWRAM_CODE size_t sanitize_save_size(uintptr_t address, size_t size) {
    address %= NUM_BANKS * BANK_SIZE;
    if((address + size) > (NUM_BANKS * BANK_SIZE))
        size = (NUM_BANKS * BANK_SIZE) - address;
    return size;
}

IWRAM_CODE void copy_save_to_ram(uintptr_t address, u8* destination, size_t size) {
    // Sanitize size
    size = sanitize_save_size(address, size);

    address = bank_check(address);
    size_t num_banks = (address + size + BANK_SIZE - 1) / BANK_SIZE;
    for(size_t n = 0; n < num_banks; n++) {
        size_t inner_size = size;
        if(n != (num_banks - 1))
            inner_size = BANK_SIZE - address;

        for(size_t i = 0; i < inner_size; i++)
            destination[i] = read_direct_single_byte_save(address + i);

        if(n != (num_banks - 1)) {
            address = bank_check(address + inner_size);
            destination += inner_size;
            size -= inner_size;
        }
    }
}