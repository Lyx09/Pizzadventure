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

    enum type nxt_blk= gs->map->blocks[x * BLOCK_SIZE + WINDOW_WIDTH *
        fall * BLOCK_SIZE].type;
    if (nxt_blk <= OPEN) //empty or open
        return fall;

    if (character->y_acc)
        return y;

    int i = 1;
    while (gs->map->blocks[x * BLOCK_SIZE + WINDOW_WIDTH * (y - i) *
            BLOCK_SIZE].type <= OPEN)
    {
        i++;
    }

    character->status = IDLE;
    return y - i;
}

void update_position(struct Character *character, enum action action,
                     struct GameState *gs)
{
    float x = character->position.x;
    float y = character->position.y;
    int index = x * BLOCK_SIZE + WINDOW_WIDTH * (y + 1) * BLOCK_SIZE;

    if (action & JUMP && gs->map->blocks[index].type != OPEN)
    {
        character->y_acc = -12.0;
        character->status |= JUMPING;
    }

    if (character->status & JUMP || gs->map->blocks[index].type == OPEN)
        character->position.y += apply_gravity(character, gs);

    index = (x - 1) * BLOCK_SIZE + WINDOW_WIDTH * y * BLOCK_SIZE;
    if ((action & LEFT) && gs->map->blocks[index].type == OPEN)
    {
        character->position.x -= 1;
        character->status |= RUNNING;
    }

    index = (x + 1) * BLOCK_SIZE + WINDOW_WIDTH * y * BLOCK_SIZE;
    if ((action & RIGHT) && gs->map->blocks[index].type == OPEN)
    {
        character->position.x += 1;
        character->status |= RUNNING;
    }

    if (!action)
        character->status &= ~RUNNING;
}
