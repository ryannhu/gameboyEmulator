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


// Load instructions:


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
    uint16_t address = emulator.memory->read(pc.get());
    pc.increment();
    address |= emulator.memory->read(pc.get()) << 8;
    pc.increment();
    rp.set(address);
}

void CPU::opcodeLoadHLN8() {
    uint8_t value = emulator.memory->read(pc.get());
    pc.increment();
    emulator.memory->write(hl.get(), value);
}

void CPU::opcodeLoadHLR8(Register &r) {
    emulator.memory->write(hl.get(), r.get());
}

void CPU::opcodeLoadR8HL(Register &r) {
    r.set(emulator.memory->read(hl.get()));
}

void CPU::opcodeLoadR16A(RegisterPair &rp) {
    opcodeLoadR16R8(rp, a);
}

void CPU::opcodeLoadN16A() {
    uint16_t address = emulator.memory->read(pc.get());
    pc.increment();
    address |= emulator.memory->read(pc.get()) << 8;
    pc.increment();
    std::cout << "address: " << (int) address << std::endl;
    emulator.memory->write(address, a.get());
}

void CPU::opcodeLoadAR16(RegisterPair &rp) {
    a.set(emulator.memory->read(rp.get()));
}


void CPU::opcodeLoadAN16() {
    uint16_t address = emulator.memory->read(pc.get());
    pc.increment();
    address |= emulator.memory->read(pc.get()) << 8;
    pc.increment();
    a.set(emulator.memory->read(address));
}

void CPU::LoadHN16A() {
    uint16_t address = emulator.memory->read(pc.get());
    pc.increment();
    address |= 0xFF00;
    emulator.memory->write(address, a.get());
}

void CPU::LoadHCA() {
    uint8_t offset = c.get();
    uint16_t address = 0xFF00 + offset;
    emulator.memory->write(address, a.get());
}

void CPU::LoadHAN16() {
    uint16_t address = emulator.memory->read(pc.get());
    pc.increment();
    address |= 0xFF00;
    a.set(emulator.memory->read(address));
}

void CPU::LoadHAC() {
    uint8_t offset = c.get();
    uint16_t address = 0xFF00 + offset;
    a.set(emulator.memory->read(address));
}

void CPU::LoadHLIA() {
    opcodeLoadHLR8(a);
    hl.increment();
}

void CPU::opcodeLoadHLDA() {
    std::cout << (int) a.get() << (int) hl.get() << std::endl;
    opcodeLoadR8HL(a);
    hl.decrement();
}

void CPU::opcodeLoadAHLD() {
    opcodeLoadR8HL(a);
    hl.decrement();
}

void CPU::opcodeLoadAHLI() {
    opcodeLoadR8HL(a);
    hl.increment();
}

void CPU::opcodeLoadSPN16() {
    uint16_t address = emulator.memory->read(pc.get());
    pc.increment();
    address |= emulator.memory->read(pc.get()) << 8;
    pc.increment();
    sp.set(address);
}

void CPU::opcodeLoadN16SP() {
    uint16_t address = emulator.memory->read(pc.get());
    pc.increment();
    address |= emulator.memory->read(pc.get()) << 8;
    pc.increment();
    emulator.memory->write(address, sp.get() & 0x00FF);
    emulator.memory->write(address + 1, sp.get() >> 8);
}

void CPU::opcodeLoadHLSPN8() {
    // get signed value, not unsigned
    int8_t e8 = emulator.memory->read(pc.get());
    pc.increment();
    int16_t result = sp.get() + e8;
    hl.set(result);
    f.setZeroFlag(false);
    f.setSubtractFlag(false);
    f.setHalfCarryFlag((sp.get() & 0x0F) + (e8 & 0x0F) > 0x0F);
    f.setCarryFlag((sp.get() & 0xFF) + e8 > 0xFF);
}

void CPU::opcodeLoadSPHL() {
    sp.set(hl.get());
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

void CPU::opcodeIncHL() {
    uint8_t value = emulator.memory->read(hl.get());
    value++;
    emulator.memory->write(hl.get(), value);
    f.setZeroFlag(value == 0);
    f.setSubtractFlag(false);
    f.setHalfCarryFlag((value & 0x0F) == 0);
}

void CPU::opcodeDecHL() {
    uint8_t value = emulator.memory->read(hl.get());
    value--;
    emulator.memory->write(hl.get(), value);
    f.setZeroFlag(value == 0);
    f.setSubtractFlag(true);
    f.setHalfCarryFlag((value & 0x0F) == 0x0F);
}

void CPU::opcodeIncSP() {
    sp.increment();
}

void CPU::opcodeDecSP() {
    sp.decrement();
}

void CPU::opcodeJpN16() {
    uint16_t address = emulator.memory->read(pc.get());
    pc.increment();
    address |= emulator.memory->read(pc.get()) << 8;
    pc.increment();
    pc.set(address);
}

void CPU::opcodeJpHL() {
    pc.set(hl.get());
}

void CPU::opcodeAndR8R8(Register &r1, Register &r2) {
    r1.set(r1.get() & r2.get());
    f.setZeroFlag(r1.get() == 0);
    f.setSubtractFlag(false);
    f.setHalfCarryFlag(true);
    f.setCarryFlag(false);
}

void CPU::opcodeOrR8R8(Register &r1, Register &r2) {
    r1.set(r1.get() | r2.get());
    f.setZeroFlag(r1.get() == 0);
    f.setSubtractFlag(false);
    f.setHalfCarryFlag(false);
    f.setCarryFlag(false);
}

void CPU::opcodeXorR8R8(Register &r1, Register &r2) {
    r1.set(r1.get() ^ r2.get());
    f.setZeroFlag(r1.get() == 0);
    f.setSubtractFlag(false);
    f.setHalfCarryFlag(false);
    f.setCarryFlag(false);
}

void CPU::opcodeXorHL() {
    uint16_t address = hl.get();
    uint8_t value = emulator.memory->read(address);
    a.set(a.get() ^ value);
    f.setZeroFlag(a.get() == 0);
    f.setSubtractFlag(false);
    f.setHalfCarryFlag(false);
    f.setCarryFlag(false);
}


void CPU::opcodeDI() {
    // disable interrupts TODO
}

// register rotate instructions
void CPU::opcodeRLCA() {
    uint8_t value = a.get();
    f.setCarryFlag(value & 0x80);
    value = (value << 1) | (value >> 7);
    a.set(value);
    f.setZeroFlag(false);
    f.setSubtractFlag(false);
    f.setHalfCarryFlag(false);
}

void CPU::opcodeRRCA() {
    uint8_t value = a.get();
    f.setCarryFlag(value & 0x01);
    value = (value >> 1) | (value << 7);
    a.set(value);
    f.setZeroFlag(false);
    f.setSubtractFlag(false);
    f.setHalfCarryFlag(false);
}


void CPU::unimplementedOpcode() {
    std::cerr << "Unimplemented opcode" << std::endl;
    exit(1);
}
