#include <SDL.h>

#include "input.h"

enum action get_input(const Uint8 *state)
{
    SDL_PumpEvents();
    enum action act = NONE;
    if (state[SDL_SCANCODE_ESCAPE])
        act |= ESCAPE;
    if (state[SDL_SCANCODE_X])
        act |= ATTACK;
    if (state[SDL_SCANCODE_SPACE])
        act |= JUMP;
    if (state[SDL_SCANCODE_LEFT] || state[SDL_SCANCODE_A])
        act |= LEFT;
    if (state[SDL_SCANCODE_RIGHT] || state[SDL_SCANCODE_D])
        act |= RIGHT;
    if (state[SDL_SCANCODE_UP] || state[SDL_SCANCODE_W])
        act |= UP;
    if (state[SDL_SCANCODE_DOWN] || state[SDL_SCANCODE_S])
        act |= DOWN;
    return act;
}
