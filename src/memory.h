#ifndef MEMORY_H
#define MEMORY_H

#include <cstdint>
#include <vector>
#include "emulator.h"
#include "io.h"
#include "timer.h"

class Memory {
public:
    Memory(Emulator &emulator);
    ~Memory() = default;

    uint8_t read(uint16_t address);
    void write(uint16_t address, uint8_t value);
    
private:
    Emulator &emulator;
    std::vector<uint8_t> memory;
    std::vector<uint8_t> workRam;
    std::vector<uint8_t> highRam;
    std::vector<uint8_t> oam;
    std::vector<uint8_t> vram;

};

#endif // MEMORY_H
