#include "character.h"
#include "map.h"

#define BLOCK_SIZE 20

float apply_gravity(struct Character *character, struct GameState *gs,
        double dt_time)
{
    dt_time = 0.7;
    float x = character->position.x; // Accurate cast ?
    float y = character->position.y;
    float g = 5 + character->y_acc;
    float speed = g * dt_time;
    float fall = speed * dt_time;

    if (character->y_acc >= 0)
        character->y_acc = 0;
    else
        character->y_acc += g * dt_time;

    int block_x = (x + character->sprite_size.x / 2) / BLOCK_SIZE;
    int block_y = y + fall;
    block_y += !character->y_acc ? character->sprite_size.y + 1 : 0;
    block_y /= BLOCK_SIZE;
    int index = block_x + MAP_WIDTH * block_y;

    if (index < 0 || index > MAP_HEIGHT * MAP_WIDTH)
        return 0;

    if (gs->map->blocks[index].type <= OPEN) //empty or open
        return fall;

    if (character->y_acc < 0)
    {
        character->y_acc = 0;
        return 0;
    }

    int i = character->sprite_size.y + 1;
    block_y = (y + i) / BLOCK_SIZE;
    index = block_x + MAP_WIDTH * block_y;

    while (index < MAP_HEIGHT * MAP_WIDTH
            && gs->map->blocks[index].type <= OPEN)
    {
        i++;
        block_y = (y + i) / BLOCK_SIZE;
        index = block_x + MAP_WIDTH * block_y;
    }

    character->status = IDLE;
    return i - character->sprite_size.y;
}

void update_position(struct Character *character, enum action action,
        struct GameState *gs, double dt_time)
{
    float x = character->position.x;
    float y = character->position.y;
    int block_x = x / BLOCK_SIZE;
    int block_y = (y - 1) / BLOCK_SIZE;
    int index = block_x + MAP_WIDTH * block_y;

    if (index < 0 || index > MAP_HEIGHT * MAP_WIDTH)
        return;

    if (action & JUMP && gs->map->blocks[index].type <= OPEN)
    {
        character->y_acc = -12.0;
        character->status |= JUMPING;
    }

    block_y = (y + character->sprite_size.y + 1) / BLOCK_SIZE;
    index = block_x + MAP_WIDTH * block_y;

    if (character->status & JUMPING || gs->map->blocks[index].type <= OPEN)
        character->position.y += apply_gravity(character, gs, dt_time);

    block_x = (x - 1) / BLOCK_SIZE;
    block_y = y / BLOCK_SIZE;
    index = block_x + MAP_WIDTH * block_y;

    if (index < 0)
        return;

    if ((action & LEFT) && gs->map->blocks[index].type <= OPEN)
    {
        character->position.x -= 0.18;
        character->status |= RUNNING;
    }

    block_x = (x + character->sprite_size.x) / BLOCK_SIZE;
    index = block_x + MAP_WIDTH * block_y;

    if (index > MAP_HEIGHT * MAP_WIDTH)
        return;

    if ((action & RIGHT) && gs->map->blocks[index].type <= OPEN)
    {
        character->position.x += 0.18;
        character->status |= RUNNING;
    }

    if (!action)
        character->status &= ~RUNNING;
}
