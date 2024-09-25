# gba-save-extractor
Custom cart-swapping ROM for extracting save data from original GBA cartridges with a GBA flashcart.

# How to use
- Download `gba-save-extractor.gba` from the latest releases, and add it to a flashcart of your choice;
- Insert the flash cart, turn on the GBA and load `gba-save-extractor.gba`;
- Press A to continue, then remove the flash cart;
- Insert the game cart with the save you want to extract, press A to continue;
- Once extraction is complete, remove the game cart from the GBA;
- Insert the flash cart once again, and press A to write the extracted save to the flashcart;
- Turn off the GBA, and copy the save file from the flashcart to the PC via the SD Card.

# Credits
- [https://github.com/Lorenzooone/Pokemon-Gen3-to-Gen-X](https://github.com/Lorenzooone/Pokemon-Gen3-to-Gen-X): Template for cartridge swappable ROM and reading save state from Pokemon Emerald.
- [https://felixjones.co.uk/mgba_gdb/vscode.html](GDB Debugging with mGBA | Felix Jones)

# License
All Pokémon names, sprites, names of related resources and the Japanese font are © Nintendo/Creatures Inc./GAME FREAK Inc.

Everything else, and the programming code, is governed by the MIT license.

# Building
Docker allows easily building without having to install the dependencies.
- To build for the GBA, while in the root of the project, run: `docker run --rm -it -v ${PWD}:/home/builder/gba-save-extractor matbonet/gba-save-extractor:gba_builder`