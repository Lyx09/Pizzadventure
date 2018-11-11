#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#ifdef DEBUG
#include <stdio.h>
#endif

#include "character.h"
#include "game.h"
#include "input.h"
#include "map.h"
#include "title.h"
#include "render.h"
#include "update.h"

void init_sdl(void)
{
    //Init SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0)
    {
        SDL_Log("SDL_Init fail: %s\n", SDL_GetError());
        exit(1);
    }
}

SDL_Window *new_window(void)
{
    //Open window
    SDL_Window *window = SDL_CreateWindow(GAME_NAME,
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            WINDOW_WIDTH,
            WINDOW_HEIGHT,
            SDL_WINDOW_INPUT_GRABBED); //idk
    if (window == NULL)
    {
        printf("Could not open window: %s\n", SDL_GetError());
        exit(1);
    }
    return window;
}

void init_img(void)
{
    //Init IMG
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
    int img_flags = IMG_INIT_JPG | IMG_INIT_PNG;
    int initialized = IMG_Init(img_flags);
    if ((initialized & img_flags) != img_flags)
    {
        printf("IMG_Init: %s\n", IMG_GetError());
        exit(1);
    }
}

SDL_Renderer *init_renderer(SDL_Window *window)
{
    //Init Renderer
    //Check output
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1,
            SDL_RENDERER_ACCELERATED);
    return renderer;
}

void init_mix(void)
{
    //Init mix
    int mix_flags = MIX_INIT_MP3 | MIX_INIT_OGG;
    int mix_ret = Mix_Init(mix_flags);
    if((mix_ret & mix_flags) != mix_flags)
    {
        printf("Mix_Init: %s\n", Mix_GetError());
        exit(1);
    }
}

void open_audio(void)
{
    //Open audio
    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY,
                MIX_DEFAULT_FORMAT, 2, 1024) == -1)
    {
        printf("Mix_OpenAudio: %s\n", Mix_GetError());
        exit(1);
    }
}

void init_ttf(void)
{
    if(TTF_Init() == -1)
    {
        printf("TTF_Init: %s\n", TTF_GetError());
        exit(2);
    }
}

void init_sdl_all(SDL_Window **window, SDL_Renderer **renderer)
{
    init_sdl();
    *window = new_window();
    init_img();
    *renderer = init_renderer(*window);
    init_mix();
    open_audio();
    init_ttf();
}

void cleanup(SDL_Window *window, SDL_Renderer *renderer)
{
    //Close everything
    SDL_DestroyRenderer(renderer);
    IMG_Quit();
    Mix_CloseAudio();
    TTF_Quit();
    while(Mix_Init(0))
        Mix_Quit();
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main(void)
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    init_sdl_all(&window, &renderer);

    //Load map
    struct Map *map = generate_map(SPAWN_MAP);
    struct Character *player = init_player();
    player->position.x = 400;   //
    player->position.y = 300;   //
    struct GameState gs =
    {
        .player = player,
        .renderer = renderer,
        .map = map,
        .is_on = 1,
        .player_sprite = get_texture(renderer, PLAYER_SPRITE),
        .tileset = get_texture(renderer, map->tileset),
        .background = get_texture(renderer, map->background),
        .enemy_sprites = NULL
    };

    title_screen(renderer);
    //SDL_RenderClear(renderer);
    const Uint8 *state = SDL_GetKeyboardState(NULL);

    while (gs.is_on)
    {
        enum action action = get_input(state);
        if (action & ESCAPE)
            gs.is_on = 0;
        #ifdef DEBUG
        printf("ACTION: %d\n", action);
        #endif
        update(&gs, action);
        render_frame(&gs);
    }

    //Show game over screen ?

    // Use at_exit ?
    cleanup(window, renderer);
    return 0;
}
