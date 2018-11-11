#include "game.h"
#include "map.h"
#include "render.h"

void render_frame(struct GameState *gs)
{
    render_map(gs);
    //Render everything
    SDL_RenderPresent(renderer);
}

void render_map(struct GameState *gs)
{
    //SDL_RenderClear(renderer);
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
    }

    for (int i = 0; i < MAP_HEIGHT; i++)
    {
        for (int j = 0; j < MAP_WIDTH; j++)
        {
            struct Block blk = map->blocks[i * MAP_WIDTH + j];
            if (blk.type == EMPTY)
                continue;
            src_rect.x = blk.tilepos.x;
            src_rect.y = blk.tilepos.y;
            dst_rect.x = j * dst_rect.w;
            dst_rect.y = i * dst_rect.h;
            SDL_RenderCopy(gs.renderer, gs.tileset, &src_rect, &dst_rect);
        }
    }
}

SDL_Texture *get_texture(char *file)
{
    SDL_Surface *surf = IMG_Load(file);
    SDL_Surface *texture = IMG_Load(IMAGE_TITLE);
    SDL_FreeSurface(surf);
    return texture;
}
