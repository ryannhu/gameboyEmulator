#include "timer.h"

Timer::Timer() {
    divider = 0;
    TimerCounter.set(0);
    timerModulo.set(0);
    timerControl.set(0);
}

void Timer::tick() {
    uint16_t olddiv = divider;

    divider++;

    bool timerUpdate = false;

    switch(timerControl.get() & (0b11)) {
        case 0b00:
            timerUpdate = (olddiv & (1 << 9) && (!(olddiv & (1 << 9))));
            break;
        case 0b01:
            timerUpdate = (olddiv & (1 << 3) && (!(olddiv & (1 << 3))));
            break;
        case 0b10:
            timerUpdate = (olddiv & (1 << 5) && (!(olddiv & (1 << 5))));
            break;
        case 0b11:
            timerUpdate = (olddiv & (1 << 7) && (!(olddiv & (1 << 7))));
            break;
    }

    if (timerUpdate && timerControl.get() & (1 << 2)) {
        TimerCounter.increment();
        if (TimerCounter.get() == 0xFF) {
            TimerCounter.set(timerModulo.get());
        }
    }
}

void Timer::write(uint16_t address, uint8_t value) {
    switch(address) {
        case 0xFF04:
            divider = 0;
            break;
        case 0xFF05:
            TimerCounter.set(value);
            break;
        case 0xFF06:
            timerModulo.set(value);
            break;
        case 0xFF07:
            timerControl.set(value);
            break;
    }
}