#ifndef PLAYER_H
#define PLAYER_H

#include <stdlib.h>
#include "game.h"
#include "input.h"

#define PLAYER_SPAWN_X 1.0
#define PLAYER_SPAWN_Y 1.0
#define JUMP_HEIGHT 45

enum status
{
    IDLE = 0,
    RUNNING = 1,
    JUMPING = 2,
    INVICIBLE = 4
};

struct vector2
{
    float x;
    float y;
};

struct Character
{
    enum status status;
    struct vector2 position;
    float y_acc;
    int health;
    struct vector2 sprite_size;
};

struct Character *init_player(void);

struct Character *init_enemy(struct vector2 position, int health);

void update_position(struct Character *character, enum action action,
                     struct GameState *gs, double dt_time);

void delete_character(struct Character *character);

#endif /* !PLAYER_H */
