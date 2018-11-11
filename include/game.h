#ifndef GAME_H
# define GAME_H

#include <SDL.h>

#define GAME_NAME "Yet Another Platformer"
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define MUSIC_GAME_LAUNCH "./resources/music/gba.mp3"
#define MUSIC_INTRO ""
#define IMAGE_TITLE "./resources/background/menu.jpg"
#define SPAWN_MAP "./maps/lvl0.map"

struct GameState
{
    SDL_Renderer *renderer;
    struct Map *map;
    struct Character *player;
    int is_on;
};

#endif /* ! GAME_H */
