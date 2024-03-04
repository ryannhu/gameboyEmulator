#include "cpu.h"


CPU::CPU(Emulator &emulator) :
    af(a, f),
    bc(b, c),
    de(d, e),
    hl(h, l),
    emulator(emulator) {}


void CPU::executeInstruction() {
    // std::cout << emulator.memory->read(pc.get()) << std::endl;
    std::cout << "Program Counter: " << pc.get() << std::endl;

    auto opcode = emulator.memory->read(pc.get());
    if (true) {
        std::cout << "Executing Opcode: " << std::hex << (int)opcode << std::endl;
    }
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
        case 0x13: // INC DE
            opcodeIncR16(de);
            break;
        case 0x14: // INC D
            opcodeIncR8(d);
            break;
        case 0x15: // DEC D
            opcodeDecR8(d);
            break;
        case 0x16: // LD D, 8
            opcodeLoadR8N8(d);
            break;
        case 0x17: // RLA
            // TODO
            unimplementedOpcode();
            break;
        case 0x18: // JR r8
            // TODO
            unimplementedOpcode();
            break;
        case 0x19: // ADD HL, DE
            opcodeAddR16R16(hl, de);
            break;
        case 0x1A: // LD A, (DE)
            // TODO
            unimplementedOpcode();
            break;
        case 0x1B: // DEC DE
            opcodeDecR16(de);
            break;
        case 0x1C: // INC E
            opcodeIncR8(e);
            break;
        case 0x1D: // DEC E
            opcodeDecR8(e);
            break;
        case 0x1E: // LD E, 8
            opcodeLoadR8N8(e);
            break;
        case 0x1F: // RRA
            // TODO
            unimplementedOpcode();
            break;
        case 0x20: // JR NZ, r8
            // TODO
            unimplementedOpcode();
            break;
        case 0x21: // LD HL, 16
            opcodeLoadR16N16(hl);
            break;
        case 0x22: // LD (HL+), A
            // TODO
            unimplementedOpcode();
            break;
        case 0x23: // INC HL
            opcodeIncR16(hl);
            break;
        case 0x24: // INC H
            opcodeIncR8(h);
            break;
        case 0x25: // DEC H
            opcodeDecR8(h);
            break;
        case 0x26: // LD H, 8
            opcodeLoadR8N8(h);
            break;
        case 0x27: // DAA 
            // TODO
            unimplementedOpcode();
            break;
        case 0x28: // JR Z, r8
            // TODO
            unimplementedOpcode();
            break;
        case 0x29: // ADD HL, HL
            // TODO
            unimplementedOpcode();
            break;
        case 0x2A: // LD A, (HL+)
            // TODO
            unimplementedOpcode();
            break;
        case 0x2B: // DEC HL
            opcodeDecR16(hl);
            break;
        case 0x2C: // INC L
            opcodeIncR8(l);
            break;
        case 0x2D: // DEC L
            opcodeDecR8(l);
            break;
        case 0x2E: // LD L, 8
            opcodeLoadR8N8(l);
            break;
        case 0x2F: // CPL
            // TODO
            unimplementedOpcode();
            break;
        case 0x30: // JR NC, r8
            // TODO
            unimplementedOpcode();
            break;
        case 0x31: // LD SP, 16
            // TODO
            unimplementedOpcode();
            break;
        case 0x32: // LD (HL-), A
            // TODO
            unimplementedOpcode();
            break;
        case 0x33: // INC SP
            // TODO
            unimplementedOpcode();
            break;
        case 0x34: // INC (HL)
            // TODO
            unimplementedOpcode();
            break;
        case 0x35: // DEC (HL)
            // TODO
            unimplementedOpcode();
            break;
        case 0x36: // LD (HL), 8
            // TODO
            unimplementedOpcode();
            break;
        case 0x37: // SCF   
            // TODO
            unimplementedOpcode();
            break;
        case 0x38: // JR C, r8
            // TODO
            unimplementedOpcode();
            break;
        case 0x39: // ADD HL, SP
            // TODO
            unimplementedOpcode();
            break;
        case 0x3A: // LD A, (HL-)
            // TODO
            unimplementedOpcode();
            break;
        case 0x3B: // DEC SP
            // TODO
            unimplementedOpcode();
            break;
        case 0x3c: // INC A
            opcodeIncR8(a);
            break;
        case 0x3D: // DEC A
            opcodeDecR8(a);
            break;
        case 0x3E: // LD A, 8
            opcodeLoadR8N8(a);
            break;
        case 0x3F: // CCF
            // TODO
            unimplementedOpcode();
            break;
        case 0x40: // LD B, B
            opcodeLoadR8R8(b, b);
            break;
        case 0x41: // LD B, C
            opcodeLoadR8R8(b, c);
            break;
        case 0x42: // LD B, D
            opcodeLoadR8R8(b, d);
            break;
        case 0x43: // LD B, E
            opcodeLoadR8R8(b, e);
            break;
        case 0x44: // LD B, H
            opcodeLoadR8R8(b, h);
            break;
        case 0x45: // LD B, L
            opcodeLoadR8R8(b, l);
            break;
        case 0x46: // LD B, (HL)
            // TODO
            unimplementedOpcode();
            break;
        case 0x47: // LD B, A
            opcodeLoadR8R8(b, a);
            break;
        case 0x48: // LD C, B
            opcodeLoadR8R8(c, b);
            break;
        case 0x49: // LD C, C
            opcodeLoadR8R8(c, c);
            break;
        case 0x4A: // LD C, D
            opcodeLoadR8R8(c, d);
            break;
        case 0x4B: // LD C, E
            opcodeLoadR8R8(c, e);
            break;
        case 0x4C: // LD C, H
            opcodeLoadR8R8(c, h);
            break;
        case 0x4D: // LD C, L
            opcodeLoadR8R8(c, l);
            break;
        case 0x4E: // LD C, (HL)
            // TODO
            unimplementedOpcode();
            break;
        case 0x4F: // LD C, A
            opcodeLoadR8R8(c, a);
            break;
        case 0x50: // LD D, B
            opcodeLoadR8R8(d, b);
            break;
        case 0x51: // LD D, C
            opcodeLoadR8R8(d, c);
            break;
        case 0x52: // LD D, D
            opcodeLoadR8R8(d, d);
            break;
        case 0x53: // LD D, E
            opcodeLoadR8R8(d, e);
            break;
        case 0x54: // LD D, H
            opcodeLoadR8R8(d, h);
            break;
        case 0x55: // LD D, L
            opcodeLoadR8R8(d, l);
            break;
        case 0x56: // LD D, (HL)
            // TODO
            unimplementedOpcode();
            break;
        case 0x57: // LD D, A
            opcodeLoadR8R8(d, a);
            break;
        case 0x58: // LD E, B
            opcodeLoadR8R8(e, b);
            break;
        case 0x59: // LD E, C
            opcodeLoadR8R8(e, c);
            break;
        case 0x5A: // LD E, D
            opcodeLoadR8R8(e, d);
            break;
        case 0x5B: // LD E, E
            opcodeLoadR8R8(e, e);
            break;
        case 0x5C: // LD E, H
            opcodeLoadR8R8(e, h);
            break;
        case 0x5D: // LD E, L
            opcodeLoadR8R8(e, l);
            break;
        case 0x5E: // LD E, (HL)
            // TODO
            unimplementedOpcode();
            break;
        case 0x5F: // LD E, A
            opcodeLoadR8R8(e, a);
            break;
        case 0x60: // LD H, B
            opcodeLoadR8R8(h, b);
            break;
        case 0x61: // LD H, C
            opcodeLoadR8R8(h, c);
            break;
        case 0x62: // LD H, D
            opcodeLoadR8R8(h, d);
            break;
        case 0x63: // LD H, E
            opcodeLoadR8R8(h, e);
            break;
        case 0x64: // LD H, H
            opcodeLoadR8R8(h, h);
            break;
        case 0x65: // LD H, L
            opcodeLoadR8R8(h, l);
            break;
        case 0x66: // LD H, (HL)
            // TODO
            unimplementedOpcode();
            break;
        case 0x67: // LD H, A   
            opcodeLoadR8R8(h, a);
            break;
        case 0x68: // LD L, B
            opcodeLoadR8R8(l, b);
            break;
        case 0x69: // LD L, C
            opcodeLoadR8R8(l, c);
            break;
        case 0x6A: // LD L, D
            opcodeLoadR8R8(l, d);
            break;
        case 0x6B: // LD L, E
            opcodeLoadR8R8(l, e);
            break;
        case 0x6C: // LD L, H
            opcodeLoadR8R8(l, h);
            break;
        case 0x6D: // LD L, L   
            opcodeLoadR8R8(l, l);
            break;
        case 0x6E: // LD L, (HL)
            // TODO
            unimplementedOpcode();
            break;
        case 0x6F: // LD L, A
            opcodeLoadR8R8(l, a);
            break;
        case 0x70: // LD (HL), B
            // TODO
            unimplementedOpcode();
            break;
        case 0x71: // LD (HL), C
            // TODO
            unimplementedOpcode();
            break;
        case 0x72: // LD (HL), D
            // TODO
            unimplementedOpcode();
            break;
        case 0x73: // LD (HL), E
            // TODO
            unimplementedOpcode();
            break;
        case 0x74: // LD (HL), H
            // TODO
            unimplementedOpcode();
            break;
        case 0x75: // LD (HL), L
            // TODO
            unimplementedOpcode();
            break;
        case 0x76: // HALT
            // TODO
            unimplementedOpcode();
            break;
        case 0x77: // LD (HL), A
            // TODO
            unimplementedOpcode();
            break;
        case 0x78: // LD A, B
            opcodeLoadR8R8(a, b);
            break;
        case 0x79: // LD A, C
            opcodeLoadR8R8(a, c);
            break;
        case 0x7A: // LD A, D
            opcodeLoadR8R8(a, d);
            break;
        case 0x7B: // LD A, E
            opcodeLoadR8R8(a, e);
            break;
        case 0x7C: // LD A, H
            opcodeLoadR8R8(a, h);
            break;
        case 0x7D: // LD A, L
            opcodeLoadR8R8(a, l);
            break;
        case 0x7E: // LD A, (HL)
            // TODO
            unimplementedOpcode();
            break;
        case 0x7F: // LD A, A
            opcodeLoadR8R8(a, a);
            break;
        case 0x80: // ADD A, B
            opcodeAddR8R8(a, b);
            break;
        case 0x81: // ADD A, C
            opcodeAddR8R8(a, c);
            break;
        case 0x82: // ADD A, D
            opcodeAddR8R8(a, d);
            break;
        case 0x83: // ADD A, E
            opcodeAddR8R8(a, e);
            break;
        case 0x84: // ADD A, H
            opcodeAddR8R8(a, h);
            break;
        case 0x85: // ADD A, L
            opcodeAddR8R8(a, l);
            break;
        case 0x86: // ADD A, (HL)
            // TODO
            unimplementedOpcode();
            break;
        case 0x87: // ADD A, A
            opcodeAddR8R8(a, a);
            break;
        case 0x88: // ADC A, B
            opcodeAdcR8R8(a, b);
            break;
        case 0x89: // ADC A, C
            opcodeAdcR8R8(a, c);
            break;
        case 0x8A: // ADC A, D
            opcodeAdcR8R8(a, d);
            break;
        case 0x8B: // ADC A, E
            opcodeAdcR8R8(a, e);
            break;
        case 0x8C: // ADC A, H
            opcodeAdcR8R8(a, h);
            break;
        case 0x8D: // ADC A, L
            opcodeAdcR8R8(a, l);
            break;
        case 0x8E: // ADC A, (HL)
            // TODO
            unimplementedOpcode();
            break;
        case 0x8F: // ADC A, A
            opcodeAdcR8R8(a, a);
            break;
        case 0x90: // SUB A, B
            opcodeSubR8R8(a, b);
            break;
        case 0x91: // SUB A, C
            opcodeSubR8R8(a, c);
            break;
        case 0x92: // SUB A, D
            opcodeSubR8R8(a, d);
            break;
        case 0x93: // SUB A, E
            opcodeSubR8R8(a, e);
            break;
        case 0x94: // SUB A, H
            opcodeSubR8R8(a, h);
            break;
        case 0x95: // SUB A, L
            opcodeSubR8R8(a, l);
            break;
        case 0x96: // SUB A, (HL)
            // TODO
            unimplementedOpcode();
            break;
        case 0x97: // SUB A, A
            opcodeSubR8R8(a, a);
            break;
        case 0x98: // SBC A, B
            // TODO
            unimplementedOpcode();
            break;
        case 0x99: // SBC A, C
            // TODO
            unimplementedOpcode();
            break;

        default:
            unimplementedOpcode();
        
        
    }
    return;
}



