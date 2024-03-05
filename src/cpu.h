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

        void stackPush(uint16_t value);
        uint16_t stackPop16();
        void stackPush(uint8_t value);
        uint8_t stackPop();

        void fetchOpcode();
        void opcodeLoadR8R8(Register &r1, Register &r2);
        void opcodeLoadR8N8(Register &r);
        void opcodeLoadR16R8(RegisterPair &rp, Register &r);
        void opcodeLoadR16N16(RegisterPair &rp);
        void opcodeLoadHLN8();
        void opcodeLoadHLR8(Register &r);
        void opcodeLoadR8HL(Register &r);
        void opcodeLoadR16A(RegisterPair &rp);
        void opcodeLoadN16A();
        void opcodeLoadAR16(RegisterPair &rp);
        void opcodeLoadAN16();

        void LoadHN16A();
        void LoadHCA();
        void LoadHAN16();
        void LoadHAC();

        void LoadHLIA();
        void opcodeLoadHLDA();
        void opcodeLoadAHLD();
        void opcodeLoadAHLI();
        void opcodeLoadSPN16();
        void opcodeLoadN16SP();
        void opcodeLoadHLSPN8();
        void opcodeLoadSPHL();

        void opcodeIncR8(Register &r);
        void opcodeDecR8(Register &r);
        void opcodeIncR16(RegisterPair &rp);
        void opcodeDecR16(RegisterPair &rp);
        void opcodeIncHL();
        void opcodeDecHL();
        void opcodeIncSP();
        void opcodeDecSP();


        void opcodeRLCA();
        void opcodeRRCA();

        void opcodeAddR16R16(RegisterPair &rp1, RegisterPair &rp2);
        void opcodeAddR8R8(Register &r1, Register &r2);
        void opcodeAdcR8R8(Register &r1, Register &r2);
        void opcodeAddR16N8(RegisterPair &rp);
        void opcodeAddR8N8(Register &r);

        void opcodeSubR8R8(Register &r1, Register &r2);
        void opcodeAndR8R8(Register &r1, Register &r2);
        void opcodeOrR8R8(Register &r1, Register &r2);
        void opcodeXorR8R8(Register &r1, Register &r2);
        void opcodeXorHL();

        void opcodeJpN16();
        void opcodeJpCCN16(const bool condition);
        void opcodeJpHL();

        void opcodeJrN16();
        void opcodeJrCCN16(const bool condition);

        void opcodeDI();

        void opcodePush(RegisterPair &rp);
        void opcodePop(RegisterPair &rp);
        void opcodePush(WordRegister &r);
        void opcodePop(WordRegister &r);

        void opcodeCallN16();
        void opcodeCallCCN16(const bool condition);
        
        void unimplementedOpcode();
};

#endif
