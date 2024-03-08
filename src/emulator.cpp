#include "emulator.h"
#include "cpu.h"

Emulator::Emulator(std::shared_ptr<Cartridge> cartridge) : cartridge(cartridge) {
    graphics = std::make_unique<Graphics>();
    cpu = std::make_unique<CPU>(*this);
    memory = std::make_unique<Memory>(*this);
    ticks = 0;
}

Emulator::~Emulator() {
}

void Emulator::run() {
    std::cout << "Running emulator" << std::endl;
    while (graphics->isRunning()) {
        cpu->step();
        // graphics->drawGameboyScreen();
        ticks++;
    }
}

void Emulator::cycles(int cpuCycles) {
    // TODO: implement
    
}