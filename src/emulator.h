#ifndef EMULATOR_H
#define EMULATOR_H

#include <iostream>
#include <memory>
#include "graphics.h"
#include "cpu.h"

class Emulator {
    public:
        Emulator();
        ~Emulator();
        void run();
    private:
        std::unique_ptr<Graphics> graphics;
        std::unique_ptr<CPU> cpu;
};

#endif