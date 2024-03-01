#ifndef CARTRIDGE_H
#define CARTRIDGE_H

#include <cstdint>
#include <memory>
#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;

class RomHeader; // Forward declaration

class Cartridge {
    public:
        Cartridge() = default;
        ~Cartridge() = default;

        void load(const string& filename);
        uint8_t read(uint16_t address);
        void write(uint16_t address, uint8_t value);

    private:
        string filename;
        uint32_t romSize;
        vector<uint8_t> romData;
        RomHeader *Header;

};

struct RomHeader {
    uint8_t entry[4];
    uint8_t logo[0x30];
    char title[16];
    uint16_t newLicenseeCode;
    uint8_t sgbFlag;
    uint8_t cartridgeType;
    uint8_t romSize;
    uint8_t ramSize;
    uint8_t destinationCode;
    uint8_t oldLicenseeCode;
    uint8_t maskROMVersion;
    uint8_t headerChecksum;
    uint16_t globalChecksum;
};

#endif // CARTRIDGE_H
