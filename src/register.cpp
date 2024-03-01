#include "register.h"

Register::Register() {
    value = 0;
}

RegisterPair::RegisterPair(Register &high, Register &low) :
    high(high), low(low) {}

void Register::set(uint8_t value) {
    this->value = value;
}

uint8_t Register::get() {
    return value;
}

void RegisterPair::set(uint16_t value) {
    high.set((value & 0xFF00) >> 8);
    low.set(value & 0x00FF);
}

