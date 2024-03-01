#include "emulator.h"
#include "cpu.h"

Emulator::Emulator() {
    graphics = std::make_unique<Graphics>();
    cpu = std::make_unique<CPU>(*this);
    memory = std::make_unique<Memory>();
}

Emulator::~Emulator() {
}

void Emulator::run() {
    std::cout << "Running emulator" << std::endl;
    while (graphics->isRunning()) {
        cpu->executeInstruction();
        graphics->drawGameboyScreen();
    }
}