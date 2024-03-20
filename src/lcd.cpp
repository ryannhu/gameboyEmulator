#include "lcd.h"

static unsigned long colors[4] = {
    0xFFFFFFFF, 0xFFAAAAAA, 0xFF555555, 0xFF000000
};

LCD::LCD(Emulator &emulator) : emulator(emulator) {
    lcdControl.set(0x91);
    lcdStatus.set(0x85);
    scrollY.set(0x00);
    scrollX.set(0x00);
    ly.set(0x00);
    lyCompare.set(0x00);
    bg_palette.set(0xFC);
    obj_palette0.set(0xFF);
    obj_palette1.set(0xFF);
    windowY.set(0x00);
    windowX.set(0x00);
    dma.set(0x00);

    for (int i = 0; i < 4; i++) {
        bgColors[i] = colors[i];
        objColors[i] = colors[i];
        windowColors[i] = colors[i];
    }

}


VideoMode LCD::getVideoMode() {
    // based on the value of the LCDS register, return the current video mode
    // 0: HBlank
    // 1: VBlank
    // 2: OAM
    // 3: VRAM
    uint8_t mode = lcdStatus.get() & 0b11;
    switch (mode) {
        case 0:
            return VideoMode::HBLANK;
        case 1:
            return VideoMode::VBLANK;
        case 2:
            return VideoMode::OAM;
        case 3:
            return VideoMode::VRAM;
    }
}