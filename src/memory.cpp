#include "memory.h"

Memory::Memory() {
    // initialize memory
    for (int i = 0; i < 0xFFFF; i++) {
        memory[i] = 0;
    }
}


uint8_t Memory::read(uint16_t address) {
    return memory[address];
}

void Memory::write(uint16_t address, uint8_t value) {
    memory[address] = value;
}