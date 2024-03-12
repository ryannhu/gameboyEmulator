#ifndef DEBUG_H
#define DEBUG_H

#include <string>
#include <iostream>
#include "memory.h"

using std::string;

class Debug {
    public:
    Debug(Memory *memory);
    ~Debug() = default;
    void update();
    void print();
    private:
        string logString;
        Memory *memory;
};

#endif // DEBUG_H