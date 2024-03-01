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
        
    }
    return;
}