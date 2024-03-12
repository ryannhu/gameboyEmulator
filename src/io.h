#ifndef IO_H
#define IO_H

#include <cstdint>

class IO {
    public:
        IO() = default;
        ~IO() = default;
        static uint8_t read(uint16_t address);
        static void write(uint16_t address, uint8_t value);
    private:
        static uint8_t serial_data[2];
};

#endif // IO_H