#include "emulator.h"
#include "cpu.h"
#include "graphics.h"
#include "ppu.h"
#include "timer.h"
#include "lcd.h"

Emulator::Emulator(std::shared_ptr<Cartridge> cartridge) : cartridge(cartridge) {
    lcd = std::make_unique<LCD>(*this);
    timer = std::make_unique<Timer>();
    io = std::make_unique<IO>(*this);
    graphics = std::make_unique<Graphics>(*this);
    ppu = std::make_unique<PPU>(*this);
    memory = std::make_unique<Memory>(*this);
    cpu = std::make_unique<CPU>(*this);
    ticks = 0;
}

Emulator::~Emulator() {
}

void Emulator::run() {
    // std::cout << "Running emulator" << std::endl;
    while (graphics->isRunning()) {
        cpu->step();
        graphics->pollEvents();
        if (ticks % 2000 == 0) {
            graphics->drawGameboyScreen();
        }
        ticks++;
    }
}

void Emulator::cycles(int cpuCycles) {
    // TODO: implement
    int n = cpuCycles * 4;
}