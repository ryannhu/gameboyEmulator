#ifndef PPU_H
#define PPU_H

#include <cstdint>
#include "oam.h"
#include "emulator.h"
#include "memory.h"
#include "lcd.h"


class PPU {
public:
    PPU(Emulator &emulator);
    ~PPU() = default;

    void tick();
    void oamWrite(uint16_t address, uint8_t value);
    uint8_t oamRead(uint16_t address);

    void vramWrite(uint16_t address, uint8_t value);
    uint8_t vramRead(uint16_t address);


    private:
        Emulator &emulator;
        LCD &lcd;
};

#endif // PPU_H
