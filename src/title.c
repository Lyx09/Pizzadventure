#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
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

void render_fonts(SDL_Renderer *renderer)
{
    int text_w = 0;
    int text_h = 0;

    TTF_Font *font = TTF_OpenFont("./resources/font/8bitlim.ttf", 50);
    SDL_Color black = {0, 0, 0, 255};

    SDL_Surface *surface_play = TTF_RenderText_Solid(font, "PLAY", black);
    SDL_Texture *texture_play = SDL_CreateTextureFromSurface(renderer,
                                                             surface_play);
    SDL_QueryTexture(texture_play, NULL, NULL, &text_w, &text_h);
    SDL_Rect dst_rect_play =
    {
        .x = 340,
        .y = 295,
        .w = text_w,
        .h = text_h
    };

    SDL_FreeSurface(surface_play);
    SDL_RenderCopy(renderer, texture_play, NULL, &dst_rect_play);
    SDL_DestroyTexture(texture_play);


    SDL_Surface *surface_quit = TTF_RenderText_Solid(font, "QUIT", black);
    SDL_Texture *texture_quit = SDL_CreateTextureFromSurface(renderer,
                                                             surface_quit);
    SDL_QueryTexture(texture_quit, NULL, NULL, &text_w, &text_h);
    SDL_Rect dst_rect_quit =
    {
        .x = 350,
        .y = 415,
        .w = text_w,
        .h = text_h
    };

    SDL_FreeSurface(surface_quit);
    SDL_RenderCopy(renderer, texture_quit, NULL, &dst_rect_quit);

    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(texture_quit);
    TTF_CloseFont(font);
}


void load_title_screen(SDL_Renderer *renderer)
{
    render_buttons(renderer);
    render_fonts(renderer);

    int mouse_x = 0;
    int mouse_y = 0;
    SDL_Event event;

    while(1)
    {
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
