#ifndef OAM_H
#define OAM_H

#include <cstdint>
#include "register.h"

class OAM {
public:
    OAM();
    ~OAM() = default;

    Register x;
    Register y;
    Register tile;

    // might need to be a different type
    FlagRegister flags;

    void operator=(const OAM &oam);
};

#endif // OAM_H