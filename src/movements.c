#include "character.h"

#define BLOCK_SIZE 20

/*
struct vector2 *jump(struct Character *character)
{
    struct vector2 position;
    struct vector2 velocity;
    struct vector2 f
}
*/

// Jump
//
// f(t) = 1/2 * gt^2 + vt + p   g gravity
//                              v initial velocity
//                              p initital position
//
// v = 2h / (th)   th time at which peak height is reached
//
// g = -2h / (th)^2   h peak height
//
// th = xh / (vx)
// v = 2h(vx) / (xh)
// g = -2h(vx)^2 / (xh)^2

float apply_gravity(struct Character *character, struct GameState *gs)
{
    float delta_time = 1 / 60;
    float g = 9.8 + character->y_acc;
    float speed = g * delta_time;
    float fall = character->y + speed * delta_time;
    character->y_acc += character->y >= 0 ? -character->y : g * delta_time;

    if (gs->map[character->x * 30 + MAP_WIDT * fall * 30] == AIR)
        return fall;

    int i = 1;

    while (gs->map[character->x * 30 + MAP_WIDT * (character->y - i) * 30] == AIR)
        i++;

    character->status = IDLE;
    return character->y - i;
}

void update_position(struct Character *character, enum action action,
                     struct GameState *gs)
{
    int index = character->x * 30 + Map_WIDTH * (character->y + 1) * 30;

    if (action & JUMP && map[index] != AIR)
    {
        character->y_acc = -12f;
        character->status |= JUMPING;
    }

    if (character->status & JUMP || map[index] == AIR)
        character->y += apply_gravity(character, gs);

    index = (character->x - 1) * 30 + MAP_WIDTH * character->y * 30;
    if ((action & LEFT) && gs->map->blocks[index].state == AIR)
    {
        character->x -= 1;
        character->status |= RUNNING;
    }

    index = (character->x + 1) * 30 + MAP_WIDTH * character->y * 30;
    if ((action & RIGHT) && gs->map->blocks[index].state == AIR)
    {
        character->x += 1;
        character->status |= RUNNING;
    }

    if (!action)
        character->status &= ~RUNNING;
}
