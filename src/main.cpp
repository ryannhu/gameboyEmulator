#include <iostream>
#include <memory>
#include <string>
#include "graphics.h"
#include "emulator.h"
#include "cartridge.h"


int main( int argc, char* args[] )
{
    // std::unique_ptr<Graphics> graphics = std::make_unique<Graphics>();
    // std::unique_ptr<Cartridge> cartridge = std::make_unique<Cartridge>();
    std::shared_ptr<Cartridge> cartridge = std::make_shared<Cartridge>();
    const std::string filename = args[1];
    cartridge->load(filename);

    std::unique_ptr<Emulator> emulator = std::make_unique<Emulator>(cartridge);
    // load file from command line
    // emulator->cartridge = std::move(cartridge);

    emulator->run();
    
    // while (graphics->isRunning()) {
    //     graphics->drawGameboyScreen();
    // }
    return 0;
}
