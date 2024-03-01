#ifndef CPU_H
#define CPU_H

#include "register.h"
#include "memory.h"
#include "emulator.h"

class CPU {
    public:
        CPU(Emulator &emulator);
        ~CPU() = default;
        void executeInstruction();

    
    private:
        Register a, b, c, d, e, h, l;
        RegisterPair af, bc, de, hl;
        WordRegister sp, pc;
        // Flags
        FlagRegister f;

        uint16_t currentAddress;
        uint16_t nextAddress;

        uint8_t currentOpcode;

        Emulator &emulator;

        void fetchOpcode();
        void opcodeLoadR8N8(Register &r);
        void opcodeLoadR16R8(RegisterPair &rp, Register &r);
        void opcodeLoadR16N16(RegisterPair &rp);
        void opcodeIncR8(Register &r);
        void opcodeDecR8(Register &r);
        void opcodeIncR16(RegisterPair &rp);
        void opcodeDecR16(RegisterPair &rp);
        void unimplementedOpcode();
};

#endif
