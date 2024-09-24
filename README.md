# gba-save-extractor
Custom ROM for extracting save data from GBA cartridges with a GBA flashcart.

# Credits
- [https://github.com/Lorenzooone/Pokemon-Gen3-to-Gen-X](https://github.com/Lorenzooone/Pokemon-Gen3-to-Gen-X): Template for cartridge swappable ROM and reading save state from Pokemon Emerald.
- [https://felixjones.co.uk/mgba_gdb/vscode.html](GDB Debugging with mGBA | Felix Jones)

# License
All Pokémon names, sprites, names of related resources and the Japanese font are © Nintendo/Creatures Inc./GAME FREAK Inc.

Everything else, and the programming code, is governed by the MIT license.

# Building
Docker allows easily building without having to install the dependencies.
- To build for the GBA, while in the root of the project, run: `docker run --rm -it -v ${PWD}:/home/builder/gba-save-extractor matbonet/gba-save-extractor:gba_builder`