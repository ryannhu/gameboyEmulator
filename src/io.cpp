#include "io.h"

void IO::write(uint16_t address, uint8_t value) {
    switch (address) {
        case 0xFF00:
            // Joypad
            break;
    }
    return;
}

uint8_t IO::read(uint16_t address) {
    switch (address) {
        case 0xFF00:
            // Joypad
            break;
        case 0xFF01:
            // Serial transfer data

            break;
        case 0xFF02:
            // Serial transfer control
            break;
        case 0xFF04:
            // Divider register
            break;
        case 0xFF05:
            // Timer counter
            break;
        case 0xFF06: 
            // Timer modulo
            break;
        case 0xFF07:
            // Timer control
            break;
        case 0xFF0F:
            // Interrupt flag
            break;
        case 0xFF40:
            // LCDC
            break;
    }
    return 0;
}