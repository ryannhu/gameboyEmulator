#include <iostream>
#include <memory>
#include <string>
#include "graphics.h"
#include "emulator.h"
#include "cartridge.h"


int main( int argc, char* args[] )
{
    // std::unique_ptr<Graphics> graphics = std::make_unique<Graphics>();
    std::unique_ptr<Emulator> emulator = std::make_unique<Emulator>();
    std::unique_ptr<Cartridge> cartridge = std::make_unique<Cartridge>();
    // load file from command line
    const std::string filename = args[1];
    cartridge->load(filename);
    // emulator->cartridge = std::move(cartridge);

    emulator->run();
    
    // while (graphics->isRunning()) {
    //     graphics->drawGameboyScreen();
    // }
    return 0;
}
