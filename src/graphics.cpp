#include "graphics.h"


Graphics::Graphics(Emulator& emulator) : emulator(emulator) {
    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow(
        "Gameboy",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_OPENGL
    );

    if (window == NULL) {
        std::cout << "Could not create window: " << SDL_GetError() << std::endl;
        running = false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    gameboyScreenTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT); 

    running = true;

    SDL_CreateWindowAndRenderer(640, 480, 0, &DebugWindow, &DebugRenderer);
    DebugTexture = SDL_CreateTexture(DebugRenderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, 640, 480);

    int windowX, windowY;
    SDL_GetWindowPosition(window, &windowX, &windowY);
    SDL_SetWindowPosition(DebugWindow, windowX + SCREEN_WIDTH + 10, windowY);
}

Graphics::~Graphics() {
    SDL_DestroyTexture(gameboyScreenTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Graphics::clear() {
    SDL_RenderClear(renderer);
}

void Graphics::present() {
    SDL_RenderPresent(renderer);
}

void Graphics::drawGameboyScreen() {
        SDL_Event event;
        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        uint32_t pixels[SCREEN_HEIGHT * SCREEN_WIDTH];

        for (int i = 0; i < SCREEN_HEIGHT * SCREEN_WIDTH; i++) {
            if (i % 2 == 0) {
                pixels[i] = 0xFFFFFFFF;
            } else {
                pixels[i] =0xFFFF0000; 
            }
        }

        // Clear the screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Draw the gameboy screen
        SDL_UpdateTexture(gameboyScreenTexture, NULL, pixels, SCREEN_WIDTH * sizeof(uint32_t));
        SDL_RenderCopy(renderer, gameboyScreenTexture, NULL, NULL);

        // Update the screen
        SDL_RenderPresent(renderer);

        updateDebugScreen();
}


void Graphics::pollEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = false;
        }
    }
}

bool Graphics::isRunning() {
    return running;
}

void Graphics::quit() {
    running = false;
}

void Graphics::Delay(uint32_t time) {
    SDL_Delay(time);
}


void Graphics::updateDebugScreen() {
    int xDraw = 0;
    int yDraw = 0;
    int tile = 0;

    SDL_Rect rc;
    rc.x = 0;
    rc.y = 0;
    rc.w = DebugSurface->w;
    rc.h = DebugSurface->h;
    SDL_FillRect(DebugSurface, &rc, 0x000000);

    uint16_t tileData = 0x8000;

    // 384 tiles to draw
    for (int y = 0; y < 24; y++) {
        for (int x = 0; x < 16; x++) {
            displayTile(DebugSurface, tileData, tile, xDraw, yDraw);
            xDraw += 8;
            tile++;
        }
        yDraw += 8;
        xDraw = 0;
    }

    SDL_UpdateTexture(DebugTexture, NULL, DebugSurface->pixels, DebugSurface->pitch);
    SDL_RenderClear(DebugRenderer);
    SDL_RenderCopy(DebugRenderer, DebugTexture, NULL, NULL);
    SDL_RenderPresent(DebugRenderer);
}

void Graphics::displayTile(SDL_Surface* surface, uint16_t tileData, uint16_t tile, int xDraw, int yDraw) {
    uint16_t tileAddress = tileData + (tile * 16);
    for (int y = 0; y < 8; y++) {
        uint8_t lowByte = emulator.memory->read(tileAddress + y);
        uint8_t highByte = emulator.memory->read(tileAddress + y + 8);
        for (int x = 0; x < 8; x++) {
            uint8_t bit = 7 - x;
            uint8_t lowBit = (lowByte >> bit) & 1;
            uint8_t highBit = (highByte >> bit) & 1;
            uint8_t color = (highBit << 1) | lowBit;
            uint32_t pixel = 0;
            switch (color) {
                case 0:
                    pixel = 0xFFFFFFFF;
                    break;
                case 1:
                    pixel = 0xFFAAAAAA;
                    break;
                case 2:
                    pixel = 0xFF555555;
                    break;
                case 3:
                    pixel = 0xFF000000;
                    break;
            }
            // putPixel(surface, xDraw + x, yDraw + y, pixel);
        }
    }
}
