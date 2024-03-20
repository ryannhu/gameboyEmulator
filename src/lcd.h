#ifndef LCD_H
#define LCD_H

#include <cstdint>
#include <vector>
#include "register.h"
#include "emulator.h"

class IO;


enum class VideoMode {
    HBLANK = 0,
    VBLANK = 1,
    OAM = 2,
    VRAM = 3
}; 


class LCD {
    public:
        LCD(Emulator &emulator);
        ~LCD() = default;
        


        Register lcdControl;
        Register lcdStatus;
        Register ly;
        Register lyCompare;
        Register scrollY;
        Register scrollX;
        Register bgPalette;
        Register objPalette0;
        Register objPalette1;
        Register windowY;
        Register windowX;
        Register dma;

        uint32_t bgColors[4];
        uint32_t objColors[4];
        uint32_t windowColors[4];

        bool lcdEnabled();
        bool windowTileMapDisplaySelect();
        bool windowDisplayEnabled();
        bool bgWindowTileDataSelect();
        bool bgTileMapDisplaySelect();
        bool objSize();
        bool objDisplayEnabled();
        bool bgDisplay();


        VideoMode getVideoMode();

        private:
            Emulator &emulator;

            const int linesPerFrame = 144;
            const int ticksPerLine = 456;
            const int yResolution = 144;
            const int xResolution = 160;

            uint32_t currentFrame;
            uint32_t currentLine;
            vector<uint32_t> frameBuffer;

            VideoMode currentMode;


};

// LCD Control Register
// Bit 7 - LCD Display Enable (0=Off, 1=On)
// Bit 6 - Window Tile Map Display Select (0=9800-9BFF, 1=9C00-9FFF)
// Bit 5 - Window Display Enable (0=Off, 1=On)
// Bit 4 - BG & Window Tile Data Select (0=8800-97FF, 1=8000-8FFF)
// Bit 3 - BG Tile Map Display Select (0=9800-9BFF, 1=9C00-9FFF)
// Bit 2 - OBJ (Sprite) Size (0=8x8, 1=8x16)
// Bit 1 - OBJ (Sprite) Display Enable (0=Off, 1=On)
// Bit 0 - BG Display (0=Off, 1=On)

#endif // LCD_H