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

    // load rom into romData
    romData.resize(romSize);
    std::cout << "Loading " << romSize << " bytes into memory" << std::endl;
    file.read((char *) &romData[0], romSize);
    file.close();

    Header = (RomHeader *) &romData[0x100];

    std::cout << "Title: " << Header->title << std::endl;
    std::cout << "Licensee Code: " << std::hex << Header->newLicenseeCode << std::endl;
    std::cout << "Cartridge Type: " << (int) Header->cartridgeType << std::endl;
    std::cout << "ROM Size: " << (int) Header->romSize << std::endl;
    std::cout << "RAM Size: " << (int) Header->ramSize << std::endl;
    std::cout << "Destination Code: " << std::hex << (int) Header->destinationCode << std::endl;
    std::cout << "Old Licensee Code: " << std::hex << (int) Header->oldLicenseeCode << std::endl;
    std::cout << "Checksum: " << (int) Header->headerChecksum << std::endl;
    // load rom header
    std::cout << "Cartridge loaded" << std::endl;
}

uint8_t Cartridge::read(uint16_t address) {
    return romData[address];
}

void Cartridge::write(uint16_t address, uint8_t value) {
    return;
}