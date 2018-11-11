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

float apply_gravity(struct Character *character, struct GameState *gs)
{
    int x = character->position.x; // Accurate cast ?
    int y = character->position.y;
    float delta_time = 1 / 60;
    float g = 9.8 + character->y_acc;
    float speed = g * delta_time;
    int fall = speed * delta_time;
    character->y_acc += y >= 0 ? -y : g * delta_time;

    int block_x = (x * BLOCK_SIZE + character->sprite_size.x / 2) / 40;
    int block_y = fall * BLOCK_SIZE;
    block_y += character->y_acc ? character->sprite_size.y : 0;
    block_y /= 30;
    int index = block_x + WINDOW_WIDTH * block_y;

    if (gs->map->blocks[index].type <= OPEN) //empty or open
        return fall;

    if (character->y_acc)
    {
        character->y_acc = 0;
        return y;
    }

    int i = 1;
    block_y = (y - i) * BLOCK_SIZE / 30;
    index = block_x + WINDOW_WIDTH * block_y;
    while (gs->map->blocks[index].type <= OPEN)
    {
        i++;
        block_y = (y - i) * BLOCK_SIZE / 30;
        index = block_x + WINDOW_WIDTH * block_y;
    }

    character->status = IDLE;
    return y - i;
}

void update_position(struct Character *character, enum action action,
                     struct GameState *gs)
{
    int x = character->position.x;
    int y = character->position.y;
    int block_x = x * BLOCK_SIZE /40;
    int block_y = (y + character->sprite_size.y + 1) * BLOCK_SIZE / 30;
    int index = block_x + WINDOW_WIDTH * block_y;

    if (action & JUMP && gs->map->blocks[index].type != OPEN)
    {
        character->y_acc = -12.0;
        character->status |= JUMPING;
    }

    if (character->status & JUMP || gs->map->blocks[index].type <= OPEN)
        character->position.y += apply_gravity(character, gs);

    block_x = (x - 1) * BLOCK_SIZE / 40;
    block_y = y * BLOCK_SIZE / 30;
    index = block_x + WINDOW_WIDTH * block_y;
    if ((action & LEFT) && gs->map->blocks[index].type <= OPEN)
    {
        character->position.x -= 1;
        character->status |= RUNNING;
    }

    block_x = (x + character->sprite_size.x) * BLOCK_SIZE / 40;
    index = block_x + WINDOW_WIDTH * block_y;
    if ((action & RIGHT) && gs->map->blocks[index].type <= OPEN)
    {
        character->position.x += 1;
        character->status |= RUNNING;
    }

    if (!action)
        character->status &= ~RUNNING;
}
