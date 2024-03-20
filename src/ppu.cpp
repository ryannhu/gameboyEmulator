#include "ppu.h"

PPU::PPU(Emulator &emulator) : emulator(emulator), lcd(*emulator.lcd)
{
}

void PPU::tick() {
    // do stuff
    
}

void PPU::oamWrite(uint16_t address, uint8_t value) {
    emulator.memory->write(address, value);
}

uint8_t PPU::oamRead(uint16_t address) {
    return emulator.memory->read(address);
}

void PPU::vramWrite(uint16_t address, uint8_t value) {
    emulator.memory->write(address, value);
}

uint8_t PPU::vramRead(uint16_t address) {
    return emulator.memory->read(address);
}