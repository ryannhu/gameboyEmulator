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

    SDL_CreateWindowAndRenderer(16 * 8 * scale, 32 * 8 * scale, 0, &DebugWindow, &DebugRenderer);

    DebugSurface = SDL_CreateRGBSurface(0, (16 * 8 * scale) + 16 * scale, 32 * 8 * scale + 64 * scale, 32, 
                    0x00FF0000, 
                    0x0000FF00, 
                    0x000000FF, 
                    0xFF000000);

    DebugTexture = SDL_CreateTexture(DebugRenderer, 
    SDL_PIXELFORMAT_ARGB8888, 
    SDL_TEXTUREACCESS_STREAMING, (16 * 8 * scale) + (16 * scale), (32 * 8 * scale) + (64 * scale));

    int windowX, windowY;
    SDL_GetWindowPosition(window, &windowX, &windowY);
    SDL_SetWindowPosition(DebugWindow, windowX + SCREEN_WIDTH + 10, windowY);
}

Graphics::~Graphics() {
    SDL_DestroyTexture(gameboyScreenTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_DestroyTexture(DebugTexture);
    SDL_DestroyRenderer(DebugRenderer);
    SDL_DestroyWindow(DebugWindow);
    SDL_Quit();
}

void Graphics::clear() {
    SDL_RenderClear(renderer);
}

void Graphics::present() {
    SDL_RenderPresent(renderer);
}

void Graphics::drawGameboyScreen() {

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
    SDL_FillRect(DebugSurface, &rc, 0xFF111111);

    uint16_t tileData = 0x8000;

    // 384 tiles to draw
    for (int y = 0; y < 24; y++) {
        for (int x = 0; x < 16; x++) {
            displayTile(DebugSurface, tileData, tile, xDraw + (x * scale), yDraw + (y * scale));
            xDraw += 8 * scale;
            tile++;
        }
        yDraw += (8 * scale);
        xDraw = 0;
    }

    SDL_UpdateTexture(DebugTexture, NULL, DebugSurface->pixels, DebugSurface->pitch);
    SDL_RenderClear(DebugRenderer);
    SDL_RenderCopy(DebugRenderer, DebugTexture, NULL, NULL);
    SDL_RenderPresent(DebugRenderer);
}

static unsigned long tileColors[4] = {0xFFFFFFFF, 0xFFAAAAAA, 0xFF555555, 0xFF000000};

void Graphics::displayTile(SDL_Surface* surface, uint16_t tileData, uint16_t tile, int xDraw, int yDraw) {
    SDL_Rect rect;

    for (int tileY = 0; tileY < 16; tileY+=2) {
        uint8_t byte1 = emulator.memory->read(tileData + (tile * 16) + tileY);
        uint8_t byte2 = emulator.memory->read(tileData + (tile * 16) + tileY + 1);

        for (int bit = 7; bit >= 0; bit--) {
            uint8_t hiBit = !!(byte1 & (1 << bit)) << 1;
            uint8_t loBit = !!(byte2 & (1 << bit));

            uint8_t color = hiBit | loBit;

            rect.x = xDraw + ((7 - bit) * scale);
            rect.y = yDraw + (tileY / 2 * scale);
            rect.w = scale;
            rect.h = scale;

            SDL_FillRect(surface, &rect, tileColors[color]);
        }
    }
}
