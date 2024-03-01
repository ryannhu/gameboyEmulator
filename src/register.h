#ifndef REGISTER_H
#define REGISTER_H

#include <cstdint>

class Register {
    public:
        Register();
        ~Register() = default;
        void set(uint8_t value);
        uint8_t get();
    private:
        uint8_t value;
};

class FlagRegister : public Register {
    public:
        FlagRegister() = default;
        ~FlagRegister() = default;
        void setZeroFlag(const bool value);
        void setSubtractFlag(bool value);
        void setHalfCarryFlag(bool value);
        void setCarryFlag(bool value);

};

class RegisterPair {
    public:
        RegisterPair(Register &high, Register &low);
        ~RegisterPair() = default;
        void set(uint16_t value);
    private:
        Register &high;
        Register &low;
};

class WordRegister {
    public:
        WordRegister() = default;
        ~WordRegister() = default;
    private:
        uint16_t value;
};


#endif
