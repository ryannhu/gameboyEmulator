#include "debug.h"

Debug::Debug(Memory *memory) : memory(memory){
    logString = "";
}

void Debug::update() {
    if (memory->read(0xFF02) == 0x81) {
        logString += memory->read(0xFF01);

        memory->write(0xFF02, 0x0);

    }
}

void Debug::print() {
    if (logString == "") {
        return;
    }
    std::cout << "DEBUG:  " << logString << std::endl;
}