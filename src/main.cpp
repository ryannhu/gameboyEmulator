#include <SDL.h>
#include <iostream>
//The window we'll be rendering to
SDL_Window* gWindow = NULL;
    
//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//The image we will load and show on the screen
SDL_Surface* gHelloWorld = NULL;

bool init();
bool loadMedia();

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

static SDL_Window* window;

int main( int argc, char* args[] )
{
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
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_Texture* gameboyScreenTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT); 


    while (true) {
        SDL_Event event;
        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                break;
            }
        }

        // Clear the screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Draw the gameboy screen
        SDL_UpdateTexture(gameboyScreenTexture, NULL, NULL, 0);
        SDL_RenderCopy(renderer, gameboyScreenTexture, NULL, NULL);

        // Update the screen
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyTexture(gameboyScreenTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
