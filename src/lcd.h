#ifndef LCD_H
#define LCD_H

#include <cstdint>
#include <vector>
#include "register.h"

class LCD {
    public:

    private:
        Register lcdControl;
        Register lcdStatus;
        Register ly;
        Register lyCompare;
        Register scrollY;
        Register scrollX;
        Register bg_palette;
        Register obj_palette0;
        Register obj_palette1;
        Register windowY;
        Register windowX;

        

};

#endif // LCD_H