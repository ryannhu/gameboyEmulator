#ifndef MEMORY_H
#define MEMORY_H

#include <cstdint>
#include <vector>
#include "emulator.h"

class Memory {
public:
    Memory(Emulator &emulator);
    ~Memory() = default;

    uint8_t read(uint16_t address);
    void write(uint16_t address, uint8_t value);
    
private:
    Emulator *emulator;
    std::vector<uint8_t> memory;
};

#endif // MEMORY_H
