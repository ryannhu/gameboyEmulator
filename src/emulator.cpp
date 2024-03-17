#include "emulator.h"
#include "cpu.h"
#include "graphics.h"
#include "ppu.h"
#include "timer.h"

Emulator::Emulator(std::shared_ptr<Cartridge> cartridge) : cartridge(cartridge) {
    timer = std::make_unique<Timer>();
    graphics = std::make_unique<Graphics>(*this);
    cpu = std::make_unique<CPU>(*this);
    memory = std::make_unique<Memory>(*this, *timer);
    ppu = std::make_unique<PPU>(*this);
    ticks = 0;
}

Emulator::~Emulator() {
}

void Emulator::run() {
    // std::cout << "Running emulator" << std::endl;
    while (graphics->isRunning()) {
        cpu->step();
        graphics->pollEvents();
        // graphics->drawGameboyScreen();
        ticks++;
    }
}

void Emulator::cycles(int cpuCycles) {
    // TODO: implement
    int n = cpuCycles * 4;
}