#include <stdio.h> // TODO: remove me
#include <unistd.h>
#include "character.h"

struct Character init_player(void)
{
    struct Character *player = malloc(sizeof(struct character));

    player->status = IDLE;
    player->position =
    {
        .x = PLAYER_SPAWN_X;
        .y = PLAYER_SPAWN_Y;
    }

    player->health = 1;
    player->y_acc = 0;

    return player;
}

struct Character init_enemy(struct vector2 position, int health)
{
    struct Character *enemy = malloc(sizeof(struct character));

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

// TODO: remove me

char get_current_input(void);
{
    char in = fgetc(stdin);

    printf("input: %c\n", in);

    return in;
}

int main(void)
{
    struct Character *player = init_player();
    char in;

    while (1)
    {
        in = get_current_input();
    }
}
