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

        Register interruptEnable;

    private:
        Register a, b, c, d, e, h, l;
        RegisterPair af, bc, de, hl;
        WordRegister sp, pc;
        // Flags
        FlagRegister f;

        bool ime = false;

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
        void opcodeRLA();
        void opcodeRRA();

        void opcodeStop();
        
        void opcodeDAA();
        void opcodeCPL();
        void opcodeCCF();
        void opcodeSCF();

        void opcodeHalt();

        void opcodeCB();

        // CB Opcodes
        void opcodeRlcR8(Register &r);
        void opcodeRlcHL();
        void opcodeRrcR8(Register &r);
        void opcodeRrcHL();
        void opcodeRlR8(Register &r);
        void opcodeRlHL();
        void opcodeRrR8(Register &r);
        void opcodeRrHL();
        void opcodeSlaR8(Register &r);
        void opcodeSlaHL();
        void opcodeSraR8(Register &r);
        void opcodeSraHL();
        void opcodeSrlR8(Register &r);
        void opcodeSrlHL();
        void opcodeSwapR8(Register &r);
        void opcodeSwapHL();
        void opcodeBitU3R8(const uint8_t n, Register &r);
        void opcodeBitU3HL(const uint8_t n);
        void opcodeSetU3R8(const uint8_t n, Register &r);
        void opcodeSetU3HL(const uint8_t n);
        void opcodeResU3R8(const uint8_t n, Register &r);
        void opcodeResU3HL(const uint8_t n);
        

        void opcodeAdcR8R8(Register &r1, Register &r2);
        void opcodeAdcR8N8(Register &r);
        void opcodeAdcHL();

        void opcodeAddR16R16(RegisterPair &rp1, RegisterPair &rp2);
        void opcodeAddR8R8(Register &r1, Register &r2);
        void opcodeAddR16N8(RegisterPair &rp);
        void opcodeAddR8N8(Register &r);
        void opcodeAddSPE8();
        void opcodeAddAHL();
        void opcodeAddHLSP();

        void opcodeSubR8R8(Register &r1, Register &r2);
        void opcodeSubR8N8(Register &r);
        void opcodeSubHL();

        void opcodeSbcR8R8(Register &r1, Register &r2);
        void opcodeSbcR8N8(Register &r);
        void opcodeSbcHL();

        void opcodeAndR8R8(Register &r1, Register &r2);
        void opcodeAndR8N8(Register &r);
        void opcodeAndHL();


        void opcodeOrR8R8(Register &r1, Register &r2);
        void opcodeOrR8N8(Register &r);
        void opcodeOrHL();

        void opcodeXorR8R8(Register &r1, Register &r2);
        void opcodeXorR8N8(Register &r);
        void opcodeXorHL();

        void opcodeCpR8R8(Register &r1, Register &r2);
        void opcodeCpR8N8(Register &r);
        void opcodeCpHL();

        void opcodeJpN16();
        void opcodeJpCCN16(const bool condition);
        void opcodeJpHL();

        void opcodeJrN16();
        void opcodeJrCCN16(const bool condition);

        void opcodeDI();
        void opcodeEI();

        void opcodePush(RegisterPair &rp);
        void opcodePop(RegisterPair &rp);
        void opcodePush(WordRegister &r);
        void opcodePop(WordRegister &r);

        void opcodeCallN16();
        void opcodeCallCCN16(const bool condition);

        void opcodeRet();
        void opcodeRetCC(const bool condition);
        void opcodeReti();

        void opcodeRstN8(const uint8_t n);


        
        void unimplementedOpcode();
};

#endif
