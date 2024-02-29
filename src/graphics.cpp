#include "graphics.h"


Graphics::Graphics() {
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



