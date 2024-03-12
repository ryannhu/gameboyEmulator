#include "cpu.h"


typedef enum Interupts {
    VBLANK = 0x01,
    LCDSTAT = 0x02,
    TIMER = 0x04,
    SERIAL = 0x08,
    JOYPAD = 0x10
} Interupts;

CPU::CPU(Emulator &emulator) :
    af(a, f),
    bc(b, c),
    de(d, e),
    hl(h, l),
    emulator(emulator) {
        // set pc to 0x100 for now
        pc.set(0x100);
    }

void CPU::step() {
    // check for interrupts
    handleInterrupts();
    executeInstruction();
}

void CPU::handleInterrupts() {
    if (ime) {
        uint8_t interruptFlags = emulator.memory->read(0xFF0F);
        uint8_t interruptEnable = emulator.memory->read(0xFFFF);
        uint8_t interrupt = interruptFlags & interruptEnable;

        if (interrupt == 0) {
            return;
        }

        std::cout << "Interrupt: " << std::hex << (int)interrupt << std::endl;

        // push pc to stack
        opcodePush(pc);

        if (interrupt & VBLANK) {
            std::cout << "VBLANK" << std::endl;
            handleInterrupts(0x40);
        } else if (interrupt & LCDSTAT) {
            std::cout << "LCDSTAT" << std::endl;
            handleInterrupts(0x48);
        } else if (interrupt & TIMER) {
            std::cout << "TIMER" << std::endl;
            handleInterrupts(0x50);
        } else if (interrupt & SERIAL) {
            std::cout << "SERIAL" << std::endl;
            handleInterrupts(0x58);
        } else if (interrupt & JOYPAD) {
            std::cout << "JOYPAD" << std::endl;
            handleInterrupts(0x60);
        }

        // disable interrupts

        ime = false;

    }
}

// handle interrupt with address
void CPU::handleInterrupts(uint16_t address) {
    // TODO
    pc.set(address);

}


void CPU::executeInstruction() {
    // std::cout << emulator.memory->read(pc.get()) << std::endl;
    std::cout << "Program Counter: " << pc.get() << std::endl;
    ++cycles;
    auto opcode = emulator.memory->read(pc.get());
    if (true) {
        std::cout << "Cycle: " << cycles << " ";
        std::cout << "Executing Opcode: " << std::hex << (int)opcode << std::endl;
        // print registers
        std::cout << "Flags: ";
        std::cout << "Z: " << f.getZeroFlag();
        std::cout << " N: " << f.getSubtractFlag();
        std::cout << " H: " << f.getHalfCarryFlag();
        std::cout << " C: " << f.getCarryFlag() << std::endl;

        std::cout << "Registers: " << std::endl;
        std::cout << " A: " << std::hex << (int)a.get() ;
        std::cout << " B: " << std::hex << (int)b.get() ;
        std::cout << " C: " << std::hex << (int)c.get() ;
        std::cout << " D: " << std::hex << (int)d.get() ;
        std::cout << " E: " << std::hex << (int)e.get() ;
        std::cout << " H: " << std::hex << (int)h.get() ;
        std::cout << " L: " << std::hex << (int)l.get() ;
        std::cout << " BC: " << std::hex << (int)bc.get();
        std::cout << " DE: " << std::hex << (int)de.get();
        std::cout << " HL: " << std::hex << (int)hl.get();
        std::cout << " SP: " << std::hex << (int)sp.get() << std::endl; 
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
            opcodeRLCA();
            break;
        case 0x08: // LD (a16), SP
            opcodeLoadN16SP();
            break;
        case 0x09: // ADD HL, BC
            opcodeAddR16R16(hl, bc);
            break;
        case 0x0A: // LD A, (BC)
            opcodeLoadAR16(bc);
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
            opcodeRRCA();
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
            opcodeRLA();
            break;
        case 0x18: // JR r8
            opcodeJrN16();
            break;
        case 0x19: // ADD HL, DE
            opcodeAddR16R16(hl, de);
            break;
        case 0x1A: // LD A, (DE)
            opcodeLoadAR16(de);
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
            opcodeRRA();
            break;
        case 0x20: // JR NZ, r8
            opcodeJrCCN16(f.getZeroFlag() == 0);
            break;
        case 0x21: // LD HL, 16
            opcodeLoadR16N16(hl);
            break;
        case 0x22: // LD (HL+), A
            LoadHLIA();
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
            opcodeDAA();
            break;
        case 0x28: // JR Z, r8
            opcodeJrCCN16(f.getZeroFlag() == 1);
            break;
        case 0x29: // ADD HL, HL
            opcodeAddR16R16(hl, hl);
            break;
        case 0x2A: // LD A, (HL+)
            opcodeLoadAHLI();
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
            opcodeCPL();
            break;
        case 0x30: // JR NC, r8
            opcodeJrCCN16(f.getCarryFlag() == 0);
            break;
        case 0x31: // LD SP, 16
            opcodeLoadSPN16();
            break;
        case 0x32: // LD (HL-), A
            opcodeLoadHLDA();
            break;
        case 0x33: // INC SP
            opcodeIncSP();
            break;
        case 0x34: // INC (HL)
            opcodeIncHL();
            break;
        case 0x35: // DEC (HL)
            opcodeDecHL();
            break;
        case 0x36: // LD (HL), 8
            opcodeLoadHLN8();
            break;
        case 0x37: // SCF   
            f.setCarryFlag(true);
            break;
        case 0x38: // JR C, r8
            opcodeJrCCN16(f.getCarryFlag() == 1);
            break;
        case 0x39: // ADD HL, SP
            opcodeAddHLSP();
            break;
        case 0x3A: // LD A, (HL-)
            opcodeLoadAHLD();
            break;
        case 0x3B: // DEC SP
            opcodeDecSP();
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
            opcodeCCF();
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
            opcodeLoadR8HL(b);
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
            opcodeLoadR8HL(c);
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
            opcodeLoadR8HL(d);
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
            opcodeLoadR8HL(e);
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
            opcodeLoadR8HL(h);
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
            opcodeLoadR8HL(l);
            break;
        case 0x6F: // LD L, A
            opcodeLoadR8R8(l, a);
            break;
        case 0x70: // LD (HL), B
            opcodeLoadHLR8(b);
            break;
        case 0x71: // LD (HL), C
            opcodeLoadHLR8(c);
            break;
        case 0x72: // LD (HL), D
            opcodeLoadHLR8(d);
            break;
        case 0x73: // LD (HL), E
            opcodeLoadHLR8(e);
            break;
        case 0x74: // LD (HL), H
            opcodeLoadHLR8(h);
            break;
        case 0x75: // LD (HL), L
            opcodeLoadHLR8(l);
            break;
        case 0x76: // HALT
            // TODO
            unimplementedOpcode();
            break;
        case 0x77: // LD (HL), A
            opcodeLoadHLR8(a);
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
            opcodeLoadR8HL(a);
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
            opcodeAddAHL();
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
            opcodeAdcHL();
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
            opcodeSubHL();
            break;
        case 0x97: // SUB A, A
            opcodeSubR8R8(a, a);
            break;
        case 0x98: // SBC A, B
            opcodeSbcR8R8(a, b);
            break;
        case 0x99: // SBC A, C
            opcodeSbcR8R8(a, c);
            break;
        case 0x9A: // SBC A, D
            opcodeSbcR8R8(a, d);
            break;
        case 0x9B: // SBC A, E
            opcodeSbcR8R8(a, e);
            break;
        case 0x9C: // SBC A, H
            opcodeSbcR8R8(a, h);
            break;
        case 0x9D: // SBC A, L
            opcodeSbcR8R8(a, l);
            break;
        case 0x9E: // SBC A, (HL)
            opcodeSbcHL();
            break;
        case 0x9F: // SBC A, A
            opcodeSbcR8R8(a, a);
            break;
        case 0xA0: // AND A, B
            opcodeAndR8R8(a, b);
            break;
        case 0xA1: // AND A, C
            opcodeAndR8R8(a, c);
            break;
        case 0xA2: // AND A, D
            opcodeAndR8R8(a, d);
            break;
        case 0xA3: // AND A, E
            opcodeAndR8R8(a, e);
            break;
        case 0xA4: // AND A, H
            opcodeAndR8R8(a, h);
            break;
        case 0xA5: // AND A, L
            opcodeAndR8R8(a, l);
            break;
        case 0xA6: // AND A, (HL)
            opcodeAndHL();
            break;
        case 0xA7: // AND A, A
            opcodeAndR8R8(a, a);
            break;
        case 0xA8: // XOR A, B
            opcodeXorR8R8(a, b);
            break;
        case 0xA9: // XOR A, C
            opcodeXorR8R8(a, c);
            break;
        case 0xAA: // XOR A, D
            opcodeXorR8R8(a, d);
            break;
        case 0xAB: // XOR A, E
            opcodeXorR8R8(a, e);
            break;
        case 0xAC: // XOR A, H
            opcodeXorR8R8(a, h);
            break;
        case 0xAD: // XOR A, L
            opcodeXorR8R8(a, l);
            break;
        case 0xAE: // XOR A, (HL)
            opcodeXorHL();
            break;
        case 0xAF: // XOR A, A
            opcodeXorR8R8(a, a);
            break;
        case 0xB0: // OR A, B
            opcodeOrR8R8(a, b);
            break;
        case 0xB1: // OR A, C
            opcodeOrR8R8(a, c);
            break;
        case 0xB2: // OR A, D
            opcodeOrR8R8(a, d);
            break;
        case 0xB3: // OR A, E
            opcodeOrR8R8(a, e);
            break;
        case 0xB4: // OR A, H
            opcodeOrR8R8(a, h);
            break;
        case 0xB5: // OR A, L
            opcodeOrR8R8(a, l);
            break;
        case 0xB6: // OR A, (HL)
            opcodeOrHL();
            break;
        case 0xB7: // OR A, A
            opcodeOrR8R8(a, a);
            break;
        case 0xB8: // CP A, B
            opcodeCpR8R8(a, b);
            break;
        case 0xB9: // CP A, C
            opcodeCpR8R8(a, c);
            break;
        case 0xBA: // CP A, D
            opcodeCpR8R8(a, d);
            break;
        case 0xBB: // CP A, E
            opcodeCpR8R8(a, e);
            break;
        case 0xBC: // CP A, H
            opcodeCpR8R8(a, h);
            break;
        case 0xBD: // CP A, L
            opcodeCpR8R8(a, l);
            break;
        case 0xBE: // CP A, (HL)
            opcodeCpHL();
            break;
        case 0xBF: // CP A, A
            opcodeCpR8R8(a, a);
            break;
        case 0XC0: // RET NZ
            opcodeRetCC(f.getZeroFlag() == 0);
            break;
        case 0xC1: // POP BC
            opcodePop(bc);
            break;
        case 0xC2: // JP NZ, a16
            opcodeJpCCN16(f.getZeroFlag() == 0);
            break; 
        case 0xC3: // JP a16
            opcodeJpN16();
            break;
        case 0xC4: // CALL NZ, a16
            opcodeCallCCN16(f.getZeroFlag() == 0);
            break;
        case 0xC5: // PUSH BC
            opcodePush(bc);
            break;
        case 0xC6: // ADD A, 8
            opcodeAddR8N8(a);
            break;
        case 0xC7: // RST 00H
            opcodeRstN8(0x00);
            break;
        case 0xC8: // RET Z
            opcodeRetCC(f.getZeroFlag() == 1);
            break;
        case 0xC9: // RET
            opcodeRet();
            break;
        case 0xCA: // JP Z, a16
            opcodeJpCCN16(f.getZeroFlag() == 1);
            break;
        case 0xCB: // PREFIX CB
            opcodeCB();
            break;
        case 0xCC: // CALL Z, a16
            opcodeCallCCN16(f.getZeroFlag() == 1);
            break;
        case 0xCD: // CALL a16
            opcodeCallN16();
            break;
        case 0xCE: // ADC A, 8
            opcodeAdcR8N8(a);
            break;
        case 0xCF: // RST 08H
            opcodeRstN8(0x08);
            break;
        case 0xD0: // RET NC
            opcodeRetCC(f.getCarryFlag() == 0);
            break;
        case 0xD1: // POP DE
            opcodePop(de);
            break;
        case 0xD2: // JP NC, a16
            opcodeJpCCN16(f.getCarryFlag() == 0);
            break;
        case 0xD4: // CALL NC, a16
            opcodeCallCCN16(f.getCarryFlag() == 0);
            break;
        case 0xD5: // PUSH DE
            opcodePush(de);
            break;
        case 0xD6: // SUB A, 8
            opcodeSubR8N8(a);
            break;
        case 0xD7: // RST 10H
            opcodeRstN8(0x10);
            break;
        case 0xD8: // RET C
            opcodeRetCC(f.getCarryFlag() == 1);
            break;
        case 0xD9: // RETI
            opcodeReti();
            break;
        case 0xDA: // JP C, a16
            opcodeJpCCN16(f.getCarryFlag() == 1);
            break;
        case 0xDC: // CALL C, a16
            opcodeCallCCN16(f.getCarryFlag() == 1);
            break;  
        case 0xDE: // SBC A, 8
            opcodeSbcR8N8(a);
            break;
        case 0xDF: // RST 18H
            opcodeRstN8(0x18);
            break;
        case 0xE0: // LD (a8), A
            LoadHN16A();
            break;
        case 0xE1: // POP HL
            opcodePop(hl);
            break;
        case 0xE2: // LD (C), A
            LoadHCA();
            break;
        case 0xE5: // PUSH HL
            opcodePush(hl);
            break;
        case 0xE6: // AND 8
            opcodeAndR8N8(a);
            break;
        case 0xE7: // RST 20H
            opcodeRstN8(0x20);
            break;
        case 0xE8: // ADD SP, r8
            opcodeAddSPE8(); 
            break;
        case 0xE9: // JP HL
            opcodeJpHL();
            break;
        case 0xEA: // LD (a16), A
            opcodeLoadN16A();
            break;
        case 0xEE: // XOR 8
            opcodeXorR8N8(a);
            break;
        case 0xEF: // RST 28H
            opcodeRstN8(0x28);
            break;
        case 0XF0: // LD A, (a8)
            LoadHAN16();
            break;
        case 0xF1: // POP AF
            opcodePop(af);
            break;

        case 0xF2: // LD A, (C)
            LoadHAC();
            break;

        case 0xF3: // DI
            opcodeDI();
            break;
        case 0xF5: // PUSH AF
            opcodePush(af);
            break;
        case 0xF6: // OR 8
            opcodeOrR8N8(a);
            break;
        case 0xF7: // RST 30H
            opcodeRstN8(0x30);
            break;
        case 0xF8: // LD HL, SP+r8
            opcodeLoadHLSPN8();
            break;
        case 0xF9: // LD SP, HL
            opcodeLoadSPHL();
            break;
        
        case 0xFA: // LD A, (a16)
            opcodeLoadAN16();
            break;
        case 0xFB: // EI
            opcodeEI();
            break;
        case 0xFE: // CP 8
            opcodeCpR8N8(a);
            break;
        case 0xFF: // RST 38H
            opcodeRstN8(0x38);
            break;
        default:
            unimplementedOpcode();  
    }
    return;
}



