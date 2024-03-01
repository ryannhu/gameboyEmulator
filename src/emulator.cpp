#include "emulator.h"

Emulator::Emulator() {
    graphics = std::make_unique<Graphics>();
    cpu = std::make_unique<CPU>();
}

Emulator::~Emulator() {
}