#include <stdio.h> // TODO: remove me
#include <unistd.h>
#include "character.h"

struct Character *init_player(void)
{
    struct Character *player = malloc(sizeof(struct Character));

    player->status = NORMAL;
    player->position.x = .0;
    player->position.y = .0;
    player->health = 100;

    return player;
}

struct Character *init_enemy(struct vector2 position, int health)
{
    struct Character *enemy = malloc(sizeof(struct Character));

    enemy->status = NORMAL;
    enemy->position = position;
    enemy->health = health;

    return enemy;
}

void update_position(struct Character *character, float x, float y)
{
    character->position.x = x;
    character->position.y = y;
}

void delete_character(struct Character *character)
{
    free(character);
}

// TODO: remove me

char get_current_input(void)
{
    char in = fgetc(stdin);

    printf("input: %c\n", in);

    return in;
}

int main(void)
{
    //struct Character *player = init_player();
    //char in;

    while (0)
    {
        //in = get_current_input();
    }
}
