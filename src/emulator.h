#ifndef EMULATOR_H
#define EMULATOR_H

#include <iostream>
#include <memory>
#include "cartridge.h"

class CPU;

class Memory;

class Graphics;

class PPU;

class Timer;

class Emulator {
    public:
        Emulator(std::shared_ptr<Cartridge> cartridge);
        ~Emulator();
        void run();
        void cycles(int cpuCycles);
        friend class CPU;
        friend class Memory;
        friend class PPU;
        friend class Graphics;
    private:
        std::unique_ptr<Graphics> graphics;
        std::unique_ptr<CPU> cpu;
        std::unique_ptr<Memory> memory;
        std::shared_ptr<Cartridge> cartridge;
        std::unique_ptr<PPU> ppu;
        std::unique_ptr<Timer> timer;
        uint64_t ticks;
};

#endif