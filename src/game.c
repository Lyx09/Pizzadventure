#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#ifdef DEBUG
#include <stdio.h>
#endif

#include "game.h"

int main(void)
{
    //Init SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0)
    {
        SDL_Log("SDL_Init fail: %s\n", SDL_GetError());
        exit(2);
    }

    //Open window
    SDL_Window *window = SDL_CreateWindow("Yet Another Platformer",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            WINDOW_WIDTH,
            WINDOW_HEIGHT,
            SDL_WINDOW_INPUT_GRABBED); //idk
    if (window == NULL)
    {
        printf("Could not open window: %s\n", SDL_GetError());
        exit(2);
    }

    //Init IMG
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
    int img_flags = IMG_INIT_JPG | IMG_INIT_PNG;
    int initialized = IMG_Init(img_flags);
    if ((initialized & img_flags) != img_flags)
    {
        printf("IMG_Init: %s\n", IMG_GetError());
        exit(2);
    }

    //Init Renderer
    //Check output
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1,
            SDL_RENDERER_ACCELERATED);

    SDL_Surface *img_title = IMG_Load(IMAGE_TITLE);
    if(!img_title)
        printf("IMG_Load: %s\n", IMG_GetError());
    SDL_Texture *texture_title = SDL_CreateTextureFromSurface(renderer,
            img_title);
    SDL_Rect src_rect = {
    .x = 0,
    .y = 0,
    .w = img_title->w,
    .h = img_title->h
    };

   SDL_Rect dst_rect = {
    .x = 0,
    .y = 0,
    .w = WINDOW_WIDTH,
    .h = WINDOW_HEIGHT
    };
    SDL_RenderCopy(renderer, texture_title, &src_rect, &dst_rect);
    SDL_RenderPresent(renderer);

    //Open audio
    //Init mix
    int mix_flags = MIX_INIT_MP3 | MIX_INIT_OGG;
    int mix_ret = Mix_Init(mix_flags);
    if((mix_ret & mix_flags) != mix_flags)
    {
        printf("Mix_Init: %s\n", Mix_GetError());
        exit(2);
    }

    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY,
                MIX_DEFAULT_FORMAT, 2, 1024) == -1)
    {
        printf("Mix_OpenAudio: %s\n", Mix_GetError());
        exit(2);
    }
    Mix_Music *music_game_launch = Mix_LoadMUS(MUSIC_GAME_LAUNCH);
    if(!music_game_launch)
    {
        printf("Mix_LoadMUS: %s\n", Mix_GetError());
    }
    if(Mix_PlayMusic(music_game_launch, 1) == -1)
    {
        printf("Mix_PlayMusic: %s\n", Mix_GetError());
    }
    SDL_Delay(3000);

    Mix_PlayingMusic();
    Mix_FreeMusic(music_game_launch);

    SDL_DestroyTexture(texture_title);
    //Run game
    while (0)
    {
        /* Game loop */
    }

    // Use at_exit ?
    //Close everything
    SDL_DestroyRenderer(renderer);
    IMG_Quit();
    Mix_CloseAudio();
    while(Mix_Init(0))
        Mix_Quit();
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
