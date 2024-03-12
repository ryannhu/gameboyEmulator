#ifndef IO_H
#define IO_H

#include <cstdint>

namespace IO {
    uint8_t read(uint16_t address);
    void write(uint16_t address, uint8_t value);
}

#endif // IO_H