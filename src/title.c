#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "character.h"
#include "game.h"

void render_buttons(SDL_Renderer *renderer)
{
    SDL_Surface *hud = IMG_Load("./resources/sprites/HUD.png");
    if(!hud)
        printf("IMG_Load: %s\n", IMG_GetError());

    SDL_Texture *texture_hud = SDL_CreateTextureFromSurface(renderer,
                                                              hud);
    SDL_Rect src_rect_btn1 = {
        .x = 2,
        .y = 3,
        .w = 206,
        .h = 75
    };

    SDL_Rect dst_rect_btn1 = {
        .x = 293,
        .y = 280,
        .w = 206,
        .h = 75
    };

    SDL_RenderCopy(renderer, texture_hud, &src_rect_btn1, &dst_rect_btn1);

    SDL_Rect src_rect_btn2 = {
        .x = 220,
        .y = 3,
        .w = 206,
        .h = 75
    };

    SDL_Rect dst_rect_btn2 = {
        .x = 293,
        .y = 400,
        .w = 206,
        .h = 75
    };

    SDL_FreeSurface(hud);
    SDL_RenderCopy(renderer, texture_hud, &src_rect_btn2, &dst_rect_btn2);
    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(texture_hud);
}

void screen_write(TTF_Font *font, const char *text, struct vector2 dst,
           SDL_Renderer *renderer)
{
    int text_w = 0;
    int text_h = 0;

    SDL_Color black = {0, 0, 0, 255};

    SDL_Surface *surface_txt = TTF_RenderText_Solid(font, text, black);
    SDL_Texture *texture_txt = SDL_CreateTextureFromSurface(renderer,
                                                            surface_txt);
    SDL_QueryTexture(texture_txt, NULL, NULL, &text_w, &text_h);
    SDL_Rect dst_rect_play =
    {
        .x = dst.x,
        .y = dst.y,
        .w = text_w,
        .h = text_h
    };

    SDL_FreeSurface(surface_txt);
    SDL_RenderCopy(renderer, texture_txt, NULL, &dst_rect_play);
    SDL_DestroyTexture(texture_txt);
}

void render_fonts(SDL_Renderer *renderer)
{
    //int text_w = 0;
    //int text_h = 0;

    TTF_Font *font = TTF_OpenFont("./resources/font/8bitlim.ttf", 50);

    struct vector2 vec_play =
    {
        .x = 340,
        .y = 295
    };

    struct vector2 vec_quit =
    {
        .x = 350,
        .y = 415
    };

    screen_write(font, "PLAY", vec_play, renderer);
    screen_write(font, "QUIT", vec_quit, renderer);
    TTF_CloseFont(font);

    font = TTF_OpenFont("./resources/font/8bitlim.ttf", 80);
    struct vector2 vec_title =
    {
        .x = 150,
        .y = 100
    };

    screen_write(font, GAME_NAME, vec_title, renderer);
    SDL_RenderPresent(renderer);
    TTF_CloseFont(font);
}


void load_layers(SDL_Renderer *renderer, Mix_Music *music_menu)
{
    render_buttons(renderer);
    render_fonts(renderer);

    int mouse_x = 0;
    int mouse_y = 0;
    SDL_Event event;

    while(1)
    {
        if (!Mix_PlayingMusic() && Mix_PlayMusic(music_menu, -1) == -1)
            printf("Mix_PlayMusic: %s\n", Mix_GetError());

        SDL_PumpEvents();
        SDL_GetMouseState(&mouse_x, &mouse_y);
        SDL_PollEvent(&event);

        if (mouse_x > 293 && mouse_x < 499 && mouse_y < 345 && mouse_y > 280)
            if (event.button.button == SDL_BUTTON(SDL_BUTTON_LEFT))
                break;

        if (mouse_x > 293 && mouse_x < 499 && mouse_y < 475 && mouse_y > 400)
            if (event.button.button == SDL_BUTTON(SDL_BUTTON_LEFT))
                exit(2);
    }
}

void load_background(SDL_Renderer *renderer)
{
    //Print Title screen
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

    SDL_FreeSurface(img_title);
    SDL_RenderCopy(renderer, texture_title, &src_rect, &dst_rect);
    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(texture_title);
}

void title_screen(SDL_Renderer *renderer)
{
    load_background(renderer);

    Mix_Music *music_game_launch = Mix_LoadMUS(MUSIC_GAME_LAUNCH);
    if(!music_game_launch)
    {
        printf("Mix_LoadMUS: %s\n", Mix_GetError());
    }
    if(Mix_PlayMusic(music_game_launch, 1) == -1)
    {
        printf("Mix_PlayMusic: %s\n", Mix_GetError());
    }

    Mix_Music *music_menu = Mix_LoadMUS(MUSIC_MENU);
    if(!music_menu)
    {
        printf("Mix_LoadMUS: %s\n", Mix_GetError());
    }

    load_layers(renderer, music_menu);

    Mix_FreeMusic(music_game_launch);
    Mix_FreeMusic(music_menu);
}
