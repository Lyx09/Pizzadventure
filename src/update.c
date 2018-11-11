#include "game.h"
#include "update.h"
#include "input.h"
#include "character.h"

void update(struct GameState *gs, enum action action, double dt_time)
{
    (void) dt_time;
    update_position(gs->player, action, gs);
}
