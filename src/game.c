#include <SDL.h>
#include "game.h"

int main(void)
{

    //Init SDL & open window
    int SDL_Init(Uint32 flags);
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0)
    {
        SDL_Log("SDL_Init fail: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("Yet Another Platformer",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          800, 600,
                                          SDL_WINDOW_INPUT_GRABBED); //idk
    if (window == NULL)
    {
        printf("Could not open window: %s\n", SDL_GetError());
        return 1;
    }
    SDL_Delay(3000);



    //Run game
    while (0)
    {
        /* Game loop */
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
