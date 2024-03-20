#ifndef REGISTER_H
#define REGISTER_H

#include <cstdint>

class Register {
    public:
        Register();
        ~Register() = default;
        void virtual set(uint8_t value);
        uint8_t get();
        void increment();
        void decrement();
        void setBit(uint8_t bit, bool value);
    protected:
        uint8_t value;
};

class FlagRegister : public Register {
    public:
        FlagRegister() = default;
        ~FlagRegister() = default;
        void set(uint8_t value) override;
        bool getZeroFlag();
        bool getSubtractFlag();
        bool getHalfCarryFlag();
        bool getCarryFlag();
        uint8_t getCarryFlagValue();
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
        uint16_t get();
        uint8_t getHigh();
        uint8_t getLow();
        void increment();
        void decrement();
    private:
        Register &high;
        Register &low;
};

class WordRegister {
    public:
        WordRegister() = default;
        ~WordRegister() = default;
        void set(uint16_t value);
        void increment();
        void decrement();
        uint16_t get();
    private:
        uint16_t value;
};


#endif
