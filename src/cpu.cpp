#include "cpu.h"


CPU::CPU(Emulator &emulator) :
    af(a, f),
    bc(b, c),
    de(d, e),
    hl(h, l),
    emulator(emulator) {}


void CPU::executeInstruction() {
    auto opcode = emulator.memory->read(pc.get());
    pc.increment();
    switch(opcode) {
        case 0x00: // NOP
            break;
        case 0x01: // LD BC, 16
            opcodeLoadR16N16(bc);
            break;
        case 0x02: // LD (BC), A
            opcodeLoadR16R8(bc, a);
            break;
        case 0x03: // INC BC
            opcodeIncR16(bc);
            break;
        case 0x04: // INC B
            opcodeIncR8(b);
            break;
        case 0x05: // DEC B
            opcodeDecR8(b);
            break;
        case 0x06: // LD B, 8
            opcodeLoadR8N8(b);
            break;
        case 0x07: // RLCA
            // TODO

            unimplementedOpcode();
            break;
        case 0x08: // LD (a16), SP
            // TODO
            unimplementedOpcode();
            break;
        case 0x09: // ADD HL, BC
            // TODO
            unimplementedOpcode();
            break;
        case 0x0A: // LD A, (BC)
            // TODO
            unimplementedOpcode();
            break;
        case 0x0B: // DEC BC
            opcodeDecR16(bc);
            break;
        case 0x0C: // INC C
            opcodeIncR8(c);
            break;
        case 0x0D: // DEC C
            opcodeDecR8(c);
            break;
        case 0x0E: // LD C, 8
            opcodeLoadR8N8(c);
            break;
        case 0x0F: // RRCA
            // TODO
            unimplementedOpcode();
            break;
        case 0x10: // STOP 0
            // TODO
            unimplementedOpcode();
            break;
        case 0x11: // LD DE, 16
            opcodeLoadR16N16(de);
            break;
        case 0x12: // LD (DE), A
            opcodeLoadR16R8(de, a);
            break;
        
    }
    return;
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
}

void CPU::opcodeDecR16(RegisterPair &rp) {
    rp.decrement();
}

void CPU::unimplementedOpcode() {
    std::cerr << "Unimplemented opcode" << std::endl;
    exit(1);
}

