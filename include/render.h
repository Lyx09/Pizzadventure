#ifndef RENDER_H
#define RENDER_H

#include "game.h"

void render_frame(struct GameState *gs);
void render_map(struct GameState *gs);
SDL_Texture *get_texture(SDL_Renderer *renderer, char *file);

#endif
