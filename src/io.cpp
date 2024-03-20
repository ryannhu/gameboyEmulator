#include "io.h"
#include "memory.h"


IO::IO(Emulator &emulator) : 
    emulator(emulator),
    timer(*(emulator.timer))
{
    serialData.reserve(2);
}


static int ly = 0;

uint8_t IO::read(uint16_t address) {
    switch (address) {
        case 0xFF00:
            // Joypad
            break;
        case 0xFF01:
            // Serial transfer data
            return serialData[0];
            break;
        case 0xFF02:
            // Serial transfer control
            return serialData[1];
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
            std::cout << "LY read" << std::endl;
            return ly++;
            break;
        case 0xFF46:
            // DMA transfer
            break;
        case 0xFF47:
            // Background palette
            break;
        case 0xFF48:
            // Object palette 0
            break;
        case 0xFF49:
            // Object palette 1
            break;
        default:
            break;
    }
    return 0;
}


void IO::write(uint16_t address, uint8_t value) {
    switch (address) {
        case 0xFF00:
            // Joypad
            break;
        case 0xFF01:
            // Serial transfer data
            serialData[0] = value;
            break;
        case 0xFF02:
            // Serial transfer control
            serialData[1] = value;
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

        case 0xFF46:
            // DMA transfer
            dmaTransfer(value); 
            break;
        case 0xFF47:
            // Background palette
            emulator.lcd->bgPalette.set(value);
            break;
        case 0xFF48:
            // Object palette 0
            emulator.lcd->objPalette0.set(value);
            break;
        case 0xFF49:
            // Object palette 1
            emulator.lcd->objPalette1.set(value);
            break;
        default:
            break;
    }
    return;
}


void IO::dmaTransfer(const uint8_t value) {
    // mutliply value by 0x100
    uint16_t address = value * 0x100;
    // todo: implement cycle accurate DMA transfer
    // need to stall CPU for 4 cycles before transfer   
    for (uint8_t i = 0x0; i <= 0x9F; ++i) {
        uint16_t source = address + i;
        uint16_t destination = 0xFE00 + i;

        // copy information from RAM to OAM
        // destination is guaranteed to be in OAM range
        emulator.memory->write(destination, emulator.memory->read(source));
    }
}