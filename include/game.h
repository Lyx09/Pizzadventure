#ifndef GAME_H
# define GAME_H

#include <SDL.h>

#define GAME_NAME "Yet Another Platformer"
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define MUSIC_GAME_LAUNCH "./resources/music/gba.mp3"
#define MUSIC_MENU "./resources/music/happy_adventure.mp3"
#define MUSIC_INTRO ""
#define IMAGE_TITLE "./resources/background/cyberpunk-street.png"
#define SPAWN_MAP "./maps/lvl1.map"
#define PLAYER_SPRITE "./resources/sprites/pizzaboi.png"

struct GameState
{
    SDL_Renderer *renderer;
    struct Map *map;
    struct Character *player;
    int is_on;
    uint64_t last_update_time;
    //Textures
    SDL_Texture *player_sprite;
    SDL_Texture *tileset; //Add multiples?
    SDL_Texture *background;
    SDL_Texture *enemy_sprites; //Add multiples ?
};

#endif /* ! GAME_H */
