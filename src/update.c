#include "game.h"
#include "update.h"
#include "input.h"
#include "character.h"

void update(struct GameState *gs, enum action action)
{
    update_position(gs->player, action, gs);
}
