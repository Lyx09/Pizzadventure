#ifndef INPUT_H
# define INPUT_H

#include <SDL.h>

enum action
{
    NONE    = 0,
    ESCAPE  = 1,
    ATTACK  = 2,
    JUMP    = 4,
    LEFT    = 8,
    RIGHT   = 16,
    UP      = 32,
    DOWN    = 64
};

enum action get_input(const Uint8 *state);

#endif /* ! INPUT_H */
