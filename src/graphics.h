#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL.h>
#include <iostream>

class Graphics {
public:
    Graphics();
    ~Graphics();

    void clear();
    void present();
    void drawGameboyScreen();
    void updateGameboyScreen();
    void pollEvents();
    bool isRunning();
    void quit();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* gameboyScreenTexture;
    bool running;
    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 288 * 2;
};

#endif
