#include "memory.h"

#include "emulator.h"

Memory::Memory(Emulator &emulator) :
    emulator(emulator)
{
    // initialize memory
    memory.resize(0xFFFF);
    workRam.resize(0x2000);
    highRam.resize(0x80);
}


uint8_t Memory::read(uint16_t address) {
    // if address is in ROM range return cartridge
    if (address < 0x8000) {
        return emulator.cartridge->read(address);
    } else if (address < 0xA000) {
        //Char map data, vram
        return 0;
    } else if (address < 0xC000) {
        // Cartridge RAM
        return emulator.cartridge->read(address);
    } else if (address < 0xE000) {
        return workRam.at(address - 0xC000);
    } else if (address < 0xFE00) {
        // echo ram
        return 0;
    } else if (address < 0xFEA0) {
        // OAM
    } else if (address < 0xFF00) {
        // unusable reserved memory
        return 0;
    } else if (address < 0xFF80) {
        // IO
        return 0;
    } else if (address < 0xFFFF) {
        // high ram
        return highRam.at(address - 0xFF80);
    } else if (address == 0xFFFF) {
        // CPU Enable register

    }
    

    // return hramRead(address);
    // if address is in VRAM range return graphics
    
    std::cout << "Unimplemented read from memory at address: " << std::hex << address << std::endl;
    return 0;
}

void Memory::write(uint16_t address, uint8_t value) {
    if (address < 0x8000) {
        emulator.cartridge->write(address, value);
    } else if (address < 0xA000) {
        //Char map data, vram
    } else if (address < 0xC000) {
        // Cartridge RAM
        emulator.cartridge->write(address, value);
    } else if (address < 0xE000) {
        workRam.at(address - 0xC000) = value;
    } else if (address < 0xFE00) {
        // echo ram
        std::cout << "Unimplemented write to memory at address: " << std::hex << address << std::endl;
        return;
    } else if (address < 0xFEA0) {
        // OAM (object attribute memory)

    } else if (address < 0xFF00) {
        // unusable reserved memory

    } else if (address < 0xFF80) {
        // IO

    } else if (address < 0xFFFF) {
        // high ram
        highRam.at(address - 0xFF80) = value;
    } else if (address == 0xFFFF) {
        // CPU Enable register

    }


    std::cout << "Unimplemented write to memory at address: " << std::hex << address << std::endl;
    
    // memory[address] = value;
}