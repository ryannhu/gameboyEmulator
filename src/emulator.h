#ifndef EMULATOR_H
#define EMULATOR_H

#include <iostream>
#include <memory>
#include "graphics.h"
#include "memory.h"

class CPU;

class Emulator {
    public:
        Emulator();
        ~Emulator();
        void run();
        friend class CPU;
    private:
        std::unique_ptr<Graphics> graphics;
        std::unique_ptr<CPU> cpu;
        // add cartridge
        // add timer
        // add memory
        std::unique_ptr<Memory> memory;
        std::shared_ptr<Cartridge> cartridge;
};

#endif