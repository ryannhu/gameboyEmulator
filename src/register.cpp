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

void Register::increment() {
    value++;
}

void Register::decrement() {
    value--;
}

void RegisterPair::set(uint16_t value) {
    high.set((value & 0xFF00) >> 8);
    low.set(value & 0x00FF);
}

uint16_t RegisterPair::get() {
    return (high.get() << 8) | low.get();
}

uint8_t RegisterPair::getHigh() {
    return high.get();
}

uint8_t RegisterPair::getLow() {
    return low.get();
}

void RegisterPair::increment() {
    set(get() + 1);
}

void RegisterPair::decrement() {
    set(get() - 1);
}

uint16_t WordRegister::get() {
    return value;
}

void WordRegister::set(uint16_t value) {
    this->value = value;
}

void WordRegister::increment() {
    value++;
}

void WordRegister::decrement() {
    value--;
}



void FlagRegister::setZeroFlag(const bool value) {
    if (value) {
        this->value |= 0x80;
    } else {
        this->value &= 0x7F;
    }
}

void FlagRegister::setSubtractFlag(bool value) {
    if (value) {
        this->value |= 0x40;
    } else {
        this->value &= 0xBF;
    }
}

void FlagRegister::setHalfCarryFlag(bool value) {
    if (value) {
        this->value |= 0x20;
    } else {
        this->value &= 0xDF;
    }
}

void FlagRegister::setCarryFlag(bool value) {
    if (value) {
        this->value |= 0x10;
    } else {
        this->value &= 0xEF;
    }
}

bool FlagRegister::getZeroFlag() {
    return value & 0x80;
}

bool FlagRegister::getSubtractFlag() {
    return value & 0x40;
}

bool FlagRegister::getHalfCarryFlag() {
    return value & 0x20;
}

bool FlagRegister::getCarryFlag() {
    return value & 0x10;
}

