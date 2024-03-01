#include "cpu.h"


CPU::CPU() :
    af(a, f),
    bc(b, c),
    de(d, e),
    hl(h, l) {}


void CPU::executeInstruction(uint8_t opcode) {

    switch(opcode) {
        case 0x00: // NOP
            break;
        case 0x01: // LD BC, 16
            opcodeLoadR16N16(bc);
            break;
        case 0x02: // LD (BC), A
            break;
    }
    return;
}

void CPU::opcodeLoadR8N8(Register &r) {
    r.set(0x01);
}

void CPU::opcodeLoadR16N16(RegisterPair &rp) {
    rp.set(0x0101);
}

