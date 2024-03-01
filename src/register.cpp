#include "register.h"

Register::Register() {
    value = 0;
}

RegisterPair::RegisterPair(Register &high, Register &low) :
    high(high), low(low) {}