#include <iostream>
#include <memory>
#include "graphics.h"
#include "emulator.h"


int main( int argc, char* args[] )
{
    std::unique_ptr<Graphics> graphics = std::make_unique<Graphics>();
    // std::unique_ptr<Emulator> emulator = std::make_unique<Emulator>();
    while (graphics->isRunning()) {
        graphics->drawGameboyScreen();
    }
    return 0;
}
