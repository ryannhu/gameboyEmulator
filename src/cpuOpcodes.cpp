#include "cpu.h"


void CPU::opcodeAddR16R16(RegisterPair &rp1, RegisterPair &rp2) {
    uint32_t result = rp1.get() + rp2.get();
    rp1.set(result);
    f.setCarryFlag(result > 0xFFFF);
    f.setHalfCarryFlag((rp1.get() & 0x0FFF) + (rp2.get() & 0x0FFF) > 0x0FFF);
    f.setSubtractFlag(false);
}

void CPU::opcodeAddR8R8(Register &r1, Register &r2) {
    uint16_t result = r1.get() + r2.get();
    f.setCarryFlag(result > 0xFF);
    f.setHalfCarryFlag((r1.get() & 0x0F) + (r2.get() & 0x0F) > 0x0F);
    f.setSubtractFlag(false);
    r1.set(result);
    f.setZeroFlag(r1.get() == 0);
}

void CPU::opcodeAdcR8R8(Register &r1, Register &r2) {
    uint16_t result = r1.get() + r2.get() + f.getCarryFlag();
    f.setCarryFlag(result > 0xFF);
    f.setHalfCarryFlag((r1.get() & 0x0F) + (r2.get() & 0x0F) + f.getCarryFlag() > 0x0F);
    f.setSubtractFlag(false);
    r1.set(result);
    f.setZeroFlag(r1.get() == 0);
}

void CPU::opcodeAddR16N8(RegisterPair &rp) {
    uint16_t n = emulator.memory->read(pc.get());
    pc.increment();
    uint32_t result = rp.get() + n;
    rp.set(result);
    f.setCarryFlag(result > 0xFF);
    f.setHalfCarryFlag((rp.get() & 0x0F) + (n & 0x0F) > 0x0F);
    f.setSubtractFlag(false);
}

void CPU::opcodeSubR8R8(Register &r1, Register &r2) {
    uint16_t result = r1.get() - r2.get();
    f.setCarryFlag(r1.get() < r2.get());
    f.setHalfCarryFlag((r1.get() & 0x0F) < (r2.get() & 0x0F));
    f.setSubtractFlag(true);
    r1.set(result);
    f.setZeroFlag(r1.get() == 0);
}


void CPU::opcodeLoadR8R8(Register &r1, Register &r2) {
    r1.set(r2.get());
}

void CPU::opcodeLoadR8N8(Register &r) {
    // get immediate value
    uint8_t value = emulator.memory->read(pc.get());
    pc.increment();
    r.set(value);
}

void CPU::opcodeLoadR16R8(RegisterPair &rp, Register &r) {
    uint16_t address = rp.get();
    emulator.memory->write(address, r.get());
}

void CPU::opcodeLoadR16N16(RegisterPair &rp) {
    rp.set(0x0101);
}

void CPU::opcodeIncR8(Register &r) {
    r.increment();
    // set flags
    f.setZeroFlag(r.get() == 0);
    f.setSubtractFlag(false);
    f.setHalfCarryFlag(false);
}

void CPU::opcodeDecR8(Register &r) {
    r.decrement();
    // set flags
    f.setZeroFlag(r.get() == 0);
    f.setSubtractFlag(true);
    f.setHalfCarryFlag(true);
}

void CPU::opcodeIncR16(RegisterPair &rp) {
    rp.increment();
    // no flags set 
}

void CPU::opcodeDecR16(RegisterPair &rp) {
    rp.decrement();
}



void CPU::unimplementedOpcode() {
    std::cerr << "Unimplemented opcode" << std::endl;
    exit(1);
}
