#ifndef MEMORY_H
#define MEMORY_H

#include <cstdint>
#include <vector>

class Memory {
public:
    Memory();
    ~Memory() = default;

    uint8_t read(uint16_t address);
    void write(uint16_t address, uint8_t value);
    
private:
    std::vector<uint8_t> memory;
};

#endif // MEMORY_H
