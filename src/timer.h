#ifndef TIMER_H
#define TIMER_H

#include <cstdint>
#include "register.h"

class Timer {
    public:
        Timer();
        ~Timer() = default;
        void tick();
        void write(uint16_t address, uint8_t value);
        uint8_t getDivider();
        uint8_t getTimerCounter();
        uint8_t getTimerModulo();
        uint8_t getTimerControl();
        void setDivider(uint8_t value);
        void setTimerCounter(uint8_t value);
        void setTimerModulo(uint8_t value);
        void setTimerControl(uint8_t value);
        friend class IO;
    private:
        uint16_t divider;
        Register TimerCounter;
        Register timerModulo;
        Register timerControl;
};

#endif // TIMER_H