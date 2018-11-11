#include <SDL_image.h>
#include "game.h"
#include "map.h"
#include "render.h"

void render_frame(struct GameState *gs)
{
    //SDL_RenderClear(renderer); ?
    render_bg(gs);
    render_map(gs);
    render_player(gs);

    //Render everything
    SDL_RenderPresent(gs->renderer);
}

void render_player(struct GameState *gs)
{
    SDL_Rect src_rect =
    {
        .x = 0,
        .y = 0,
        .w = gs->player->sprite_size.x,
        .h = gs->player->sprite_size.y
    };
    SDL_Rect dst_rect =
    {
        .x = gs->player->position.x,
        .y = gs->player->position.y,
        .w = gs->player->sprite_size.x,
        .h = gs->player->sprite_size.y
    };
    SDL_RenderCopy(gs->renderer, gs->player_sprite, &src_rect, &dst_rect);
}

void render_bg(struct GameState *gs)
{
    int texture_w, texture_h;
    SDL_QueryTexture(gs->background, NULL, NULL, &texture_w, &texture_h);
    SDL_Rect src_rect =
    {
        .x = 0,
        .y = 0,
        .w = texture_w,
        .h = texture_h
    };
    SDL_Rect dst_rect =
    {
        .x = 0,
        .y = 0,
        .w = texture_w, // :/
        .h = texture_h
    };
    SDL_RenderCopy(gs->renderer, gs->background, &src_rect, &dst_rect);
}

void render_map(struct GameState *gs)
{
    struct Map *map = gs->map;
    SDL_Rect src_rect =
    {
        .x = 0,
        .y = 0,
        .w = map->tilesize.x,
        .h = map->tilesize.y
    };
    SDL_Rect dst_rect =
    {
        .x = 0,
        .y = 0,
        .w = WINDOW_WIDTH / 40, // :/
        .h = WINDOW_HEIGHT / 30
    };

    for (int i = 0; i < MAP_HEIGHT; i++)
    {
        for (int j = 0; j < MAP_WIDTH; j++)
        {
            struct Block blk = map->blocks[i * MAP_WIDTH + j];

            if (blk.type == EMPTY)
                continue;

            src_rect.x = blk.tilepos.x * src_rect.w;
            src_rect.y = blk.tilepos.y * src_rect.h;
            dst_rect.x = j * dst_rect.w;
            dst_rect.y = i * dst_rect.h;
            SDL_RenderCopy(gs->renderer, gs->tileset, &src_rect, &dst_rect);
        }
    }
}

SDL_Texture *get_texture(SDL_Renderer *renderer, char *file)
{
    SDL_Surface *surf = IMG_Load(file);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surf);
    SDL_FreeSurface(surf);
    return texture;
}
