#include "io.h"

uint8_t IO::serial_data[2] = {0, 0}; // Initialization outside the class definition.

IO::IO(Timer &timer) : timer(timer) {
}


void IO::write(uint16_t address, uint8_t value) {
    switch (address) {
        case 0xFF00:
            // Joypad
            break;
        case 0xFF01:
            // Serial transfer data
            serial_data[0] = value;
            break;
        case 0xFF02:
            // Serial transfer control
            serial_data[1] = value;
            break;

        case 0xFF04:
            // Divider register
            timer.divider = 0;
            break;
        case 0xFF05:
            // Timer counter
            timer.TimerCounter.set(value);
            break;
        case 0xFF06:
            // Timer modulo
            timer.timerModulo.set(value);
            break;
        case 0xFF07:
            // Timer control
            timer.timerControl.set(value);
            break;
        case 0xFF0F:
            // Interrupt flag
            break;
        case 0xFF40:

        case 0xFF44:
            // LY
            break;
        default:
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
            return serial_data[0];
            break;
        case 0xFF02:
            // Serial transfer control
            return serial_data[1];
            break;
        case 0xFF04:
            // Divider register
            return timer.divider >> 8;
            break;
        case 0xFF05:
            // Timer counter
            return timer.TimerCounter.get();
        case 0xFF06: 
            // Timer modulo
            return timer.timerModulo.get();
        case 0xFF07:
            // Timer control
            return timer.timerControl.get();
        case 0xFF0F:
            // Interrupt flag
            break;
        case 0xFF40:
            // LCDC
            break;
        case 0xFF44:
            // LY
            return 0x90;
            break;
    }
    return 0;
}