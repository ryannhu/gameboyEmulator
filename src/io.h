#ifndef IO_H
#define IO_H

#include <cstdint>
#include "timer.h"

class IO {
    public:
        IO(Timer &timer);
        ~IO() = default;
        uint8_t read(uint16_t address);
        void write(uint16_t address, uint8_t value);
    private:
        static uint8_t serial_data[2];
        Timer &timer;
};

#endif // IO_H