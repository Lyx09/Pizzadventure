#include "character.h"
#include "map.h"

#define BLOCK_SIZE 20

// Jump
//
// f(t) = 1/2 * gt^2 + vt + p   g gravity
//                              v initial velocity
//                              p initital position
//
// v = 2h / (th)   th time at which peak height is reached
//
// g = -2h / (th)^2   h peak height

float apply_gravity(struct Character *character, struct GameState *gs,
                    double dt_time)
{
    dt_time = 0.5;
    int x = character->position.x; // Accurate cast ?
    int y = character->position.y;
    float g = 9.8 + character->y_acc;
    float speed = g * dt_time;
    int fall = speed * dt_time;
    if (character->y_acc >= 0)
        character->y_acc = 0;
    else
        character->y_acc += g * dt_time;

    int block_x = (x + character->sprite_size.x / 2) / BLOCK_SIZE;
    int block_y = fall;
    block_y += character->y_acc ? character->sprite_size.y : 0;
    block_y /= BLOCK_SIZE;
    int index = block_x + MAP_WIDTH * block_y;
    if (index < 0 || index > MAP_HEIGHT * MAP_WIDTH)
        return y;

    if (gs->map->blocks[index].type <= OPEN) //empty or open
        return fall;

    if (character->y_acc)
    {
        character->y_acc = 0;
        return y;
    }

    int i = 1;
    block_y = (y - i) / BLOCK_SIZE;
    index = block_x + MAP_WIDTH * block_y;
    while (index > 0 && gs->map->blocks[index].type <= OPEN)
    {
        i++;
        block_y = (y - i) / BLOCK_SIZE;
        index = block_x + MAP_WIDTH * block_y;
    }

    character->status = IDLE;
    return y - i;
}

void update_position(struct Character *character, enum action action,
                     struct GameState *gs, double dt_time)
{
    int x = character->position.x;
    int y = character->position.y;
    int block_x = x / BLOCK_SIZE;
    int block_y = (y + character->sprite_size.y + 1) / BLOCK_SIZE;
    int index = block_x + MAP_WIDTH * block_y;
    if (index < 0 || index > MAP_HEIGHT * MAP_WIDTH)
        return;

    if (action & JUMP && gs->map->blocks[index].type != OPEN)
    {
        character->y_acc = -12.0;
        character->status |= JUMPING;
    }

    if (character->status & JUMP || gs->map->blocks[index].type <= OPEN)
        character->position.y += apply_gravity(character, gs, dt_time);

    block_x = (x - 1) / BLOCK_SIZE;
    block_y = y / BLOCK_SIZE;
    index = block_x + MAP_WIDTH * block_y;
    if (index < 0)
        return;
    if ((action & LEFT) && gs->map->blocks[index].type <= OPEN)
    {
        character->position.x -= 1;
        character->status |= RUNNING;
    }

    block_x = (x + character->sprite_size.x) / BLOCK_SIZE;
    index = block_x + MAP_WIDTH * block_y;
    if (index > MAP_HEIGHT * MAP_WIDTH)
        return;
    if ((action & RIGHT) && gs->map->blocks[index].type <= OPEN)
    {
        character->position.x += 1;
        character->status |= RUNNING;
    }

    if (!action)
        character->status &= ~RUNNING;
}
