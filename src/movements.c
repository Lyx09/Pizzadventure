#include "character.h"

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
    float x = character->position.x;
    float y = character->position.y;
    float delta_time = 1 / 60;
    float g = 9.8 + character->y_acc;
    float speed = g * delta_time;
    float fall = speed * delta_time;
    character->y_acc += y >= 0 ? -y : g * delta_time;

    if (gs->map->blocks[x * 30 + WINDOW_WIDTH * fall * 30] == OPEN)
        return fall;

    if (character->y_acc)
        return y;

    int i = 1;
    while (gs->map->blocks[x * 30 + WINDOW_WIDTH * (y - i) * 30] == OPEN)
        i++;

    character->status = IDLE;
    return y - i;
}

void update_position(struct Character *character, enum action action,
                     struct GameState *gs)
{
    float x = character->position.x;
    float y = character->position.y;
    int index = x * 30 + WINDOW_WIDTH * (y + 1) * 30;

    if (action & JUMP && gs->map->blocks[index] != OPEN)
    {
        character->y_acc = -12.0;
        character->status |= JUMPING;
    }

    if (character->status & JUMP || gs->map->blocks[index] == OPEN)
        character->position.y += apply_gravity(character, gs);

    index = (x - 1) * 30 + WINDOW_WIDTH * y * 30;
    if ((action & LEFT) && gs->map->blocks[index].state == OPEN)
    {
        character->position.x -= 1;
        character->status |= RUNNING;
    }

    index = (x + 1) * 30 + WINDOW_WIDTH * y * 30;
    if ((action & RIGHT) && gs->map->blocks[index].state == OPEN)
    {
        character->position.x += 1;
        character->status |= RUNNING;
    }

    if (!action)
        character->status &= ~RUNNING;
}
