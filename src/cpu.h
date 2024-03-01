#ifndef CPU_H
#define CPU_H

#include "register.h"

class CPU {
    public:
        CPU();
        ~CPU() = default;
        void executeInstruction(uint8_t opcode);

    
    private:
        Register a, b, c, d, e, h, l;
        RegisterPair af, bc, de, hl;
        WordRegister sp, pc;
        // Flags
        FlagRegister f;

};

#endif
