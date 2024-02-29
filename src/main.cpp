#include <iostream>
#include <memory>
#include "graphics.h"


int main( int argc, char* args[] )
{
    std::unique_ptr<Graphics> graphics = std::make_unique<Graphics>();
    while (graphics->isRunning()) {
        graphics->drawGameboyScreen();
    }

    return 0;
}
