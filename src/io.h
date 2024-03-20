#ifndef IO_H
#define IO_H

#include <cstdint>
#include <vector>
#include "timer.h"
#include "emulator.h"
#include "lcd.h"

using std::vector;


class IO {
    public:
        IO(Emulator &emulator);
        ~IO() = default;
        uint8_t read(uint16_t address);
        void write(uint16_t address, uint8_t value);
    private:
        Emulator &emulator;
        Timer &timer;

        void dmaTransfer(const uint8_t value);
        
        vector<uint8_t> serialData;
        uint8_t serialData0;
        uint8_t serialData1;
};

#endif // IO_H