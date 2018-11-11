#include <unistd.h>
#include "character.h"

struct Character *init_player(void)
{
    struct Character *player = malloc(sizeof(struct Character));

    player->status = IDLE;
    player->position.x = PLAYER_SPAWN_X;
    player->position.y = PLAYER_SPAWN_Y;
    player->health = 1;
    player->y_acc = 0;

    return player;
}

struct Character *init_enemy(struct vector2 position, int health)
{
    struct Character *enemy = malloc(sizeof(struct Character));

    enemy->status = IDLE;
    enemy->position = position;
    enemy->health = health;
    enemy->y_acc = 0;

    return enemy;
}

void delete_character(struct Character *character)
{
    free(character);
}
