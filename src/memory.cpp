#include "memory.h"

#include "emulator.h"

Memory::Memory(Emulator &emulator) :
    emulator(&emulator)
{
    // initialize memory
    
}


uint8_t Memory::read(uint16_t address) {
    // if address is in ROM range return cartridge
    if (address < 0x8000) {
        return emulator->cartridge->read(address);
    }
    // if address is in VRAM range return graphics
    
    std::cout << "Unimplemented read from memory at address: " << std::hex << address << std::endl;
    return 0;
}

void Memory::write(uint16_t address, uint8_t value) {
    if (address < 0x8000) {
        emulator->cartridge->write(address, value);
    }
    std::cout << "Unimplemented write to memory at address: " << std::hex << address << std::endl;
    
    // memory[address] = value;
}