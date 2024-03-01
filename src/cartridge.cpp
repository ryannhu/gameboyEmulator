#include "cartridge.h"

#include <fstream> // Include the necessary header file for std::ifstream



void Cartridge::load(const string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return;
    }

    file.seekg(0, std::ios::end);
    romSize = file.tellg();

    // rewind file
    file.clear();
    file.seekg(0, std::ios::beg);

    // load rom into memory
    memory.resize(romSize);
    file.read((char *) &memory[0], romSize);
    file.close();

    Header = (RomHeader *) &memory[0x100];

    std::cout << "Title: " << Header->title << std::endl;
    std::cout << "Cartridge Type: " << (int) Header->cartridgeType << std::endl;
    std::cout << "ROM Size: " << (int) Header->romSize << std::endl;
    std::cout << "RAM Size: " << (int) Header->ramSize << std::endl;
    // load rom header
    file.open(filename, std::ios::binary);
}