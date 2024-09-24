#include "base_include.h"
#include "save.h"
#include <stddef.h>


#include <gba_console.h>
#include <gba_interrupt.h>
#include <gba_systemcalls.h>
#include <gba_input.h>
#include <stdio.h>
#include <stdlib.h>

enum STATE {MAIN_MENU, EXTRACT_REQUEST_GAME, EXTRACT, EXTRACT_REQUEST_FLASHCART, EXTRACT_SUCCESS};
enum STATE curr_state;
u32 pressed_keys;
//---------------------------------------------------------------------------------
// Program entry point
//---------------------------------------------------------------------------------
int main(void) {
//---------------------------------------------------------------------------------
	// the vblank interrupt must be enabled for VBlankIntrWait() to work
	// since the default dispatcher handles the bios flags no vblank handler
	// is required
	irqInit();
	irqEnable(IRQ_VBLANK);

	consoleDemoInit();

	iprintf("");
	curr_state = MAIN_MENU;

	while (1) {
		iprintf("\x1b[2J");
		scanKeys();
		pressed_keys = keysDown();
		

		// if(pressed_keys) {
		// 	iprintf("\x1b[2J");
		// 	printf("0x%08lx\n", );
		// }

		switch(curr_state){
			case MAIN_MENU:
				printf("\x1b[4;3H-- GBA Save Extractor --");
				printf("\x1b[7;5HPress (A) to start...");
				printf("\x1b[18;1HmatBonet/gba-save-extractor");
				if(pressed_keys & KEY_A) {
					curr_state = EXTRACT_REQUEST_GAME;
				}
				break;
			case EXTRACT_REQUEST_GAME:
				printf("Please remove the flash\ncartridge and insert the game cartridge.\n A: Continue\n B: Return");
				if(pressed_keys & KEY_A) {
					curr_state = EXTRACT;
				}
				else if(pressed_keys & KEY_B) {
					curr_state = MAIN_MENU;
				}
				break;
			case EXTRACT:
				printf("\x1b[7;5HExtracting Save Data...");
				// copy_save_to_ram();


			case EXTRACT_REQUEST_FLASHCART:
				printf("Save data successfully copied to memory. Please remove the game cartridge and insert the flash cartridge.\n A: Continue");
				if(pressed_keys & KEY_A) {
					curr_state = EXTRACT_SUCCESS;
				}
				break;
			case EXTRACT_SUCCESS:
				printf("Save data sucessfully exported! You may now turn off the device.");
				break;
		}
		VBlankIntrWait();
	}	
}