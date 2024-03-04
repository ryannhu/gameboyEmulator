#ifndef EMULATOR_H
#define EMULATOR_H

#include <iostream>
#include <memory>
#include "graphics.h"
#include "cartridge.h"

class CPU;

class Memory;

class Emulator {
    public:
        Emulator(std::shared_ptr<Cartridge> cartridge);
        ~Emulator();
        void run();
        void cycles(int cpuCycles);
        friend class CPU;
        friend class Memory;
    private:
        std::unique_ptr<Graphics> graphics;
        std::unique_ptr<CPU> cpu;
        std::unique_ptr<Memory> memory;
        std::shared_ptr<Cartridge> cartridge;
        uint64_t ticks;
};

#endif