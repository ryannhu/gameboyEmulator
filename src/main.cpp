#include <iostream>
#include <memory>
#include <string>
#include "graphics.h"
#include "emulator.h"
#include "cartridge.h"


int main( int argc, char* args[] )
{
    std::unique_ptr<Graphics> graphics = std::make_unique<Graphics>();
    // std::unique_ptr<Emulator> emulator = std::make_unique<Emulator>();
    std::unique_ptr<Cartridge> cartridge = std::make_unique<Cartridge>();
    const std::string filename = "pokemon.gb";
    cartridge->load(filename);
    while (graphics->isRunning()) {
        graphics->drawGameboyScreen();
    }
    return 0;
}
