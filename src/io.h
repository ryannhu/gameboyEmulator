#ifndef IO_H
#define IO_H

#include <cstdint>
#include <vector>
#include "timer.h"

using std::vector;

class Memory;

class IO {
    public:
        IO(Timer &timer, Memory &memory);
        ~IO() = default;
        uint8_t read(uint16_t address);
        void write(uint16_t address, uint8_t value);
    private:
        Timer &timer;
        Memory &memory;
        void dmaTransfer(const uint8_t value);
        
        uint8_t serialData0;
        uint8_t serialData1;
};

#endif // IO_H