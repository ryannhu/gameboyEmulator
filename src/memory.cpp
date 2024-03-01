#include "memory.h"

Memory::Memory() {
    // initialize memory

}


uint8_t Memory::read(uint16_t address) {
    return memory[address];
}

void Memory::write(uint16_t address, uint8_t value) {
    memory[address] = value;
}