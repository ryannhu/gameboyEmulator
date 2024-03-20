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

class LCD;

class IO;

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
        friend class Timer;
        friend class LCD;
        friend class IO;
    private:
        std::unique_ptr<Graphics> graphics;
        std::unique_ptr<CPU> cpu;
        std::unique_ptr<Memory> memory;
        std::shared_ptr<Cartridge> cartridge;
        std::unique_ptr<PPU> ppu;
        std::unique_ptr<Timer> timer;
        std::unique_ptr<LCD> lcd;
        std::unique_ptr<IO> io;
        uint64_t ticks;
};

#endif