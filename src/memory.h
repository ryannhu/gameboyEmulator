#ifndef MEMORY_H
#define MEMORY_H

#include <cstdint>

class Memory {
public:
    Memory();
    ~Memory() = default;

    uint8_t read(uint16_t address);
    void write(uint16_t address, uint8_t value);
    
private:
    uint8_t memory[0xFFFF];
};

#endif // MEMORY_H
