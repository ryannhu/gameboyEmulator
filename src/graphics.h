#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL.h>
#include <iostream>
#include "emulator.h"
#include "memory.h"

class Graphics {
public:
    Graphics(Emulator &emulator);
    ~Graphics();

    void clear();
    void present();
    void drawGameboyScreen();
    void updateGameboyScreen();
    void pollEvents();
    bool isRunning();
    void quit();

    void updateDebugScreen();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* gameboyScreenTexture;
    SDL_Surface* gameboyScreenSurface;

    SDL_Window* DebugWindow;
    SDL_Renderer* DebugRenderer;
    SDL_Texture* DebugTexture;
    SDL_Surface* DebugSurface;

    void displayTile(SDL_Surface* surface, uint16_t tileData, uint16_t tile, int xDraw, int yDraw);

    Emulator &emulator;
    bool running;
    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 288 * 2;

    void Delay(uint32_t time);
};

#endif
