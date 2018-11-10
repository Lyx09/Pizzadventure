#include <stdlib.h>

enum status
{
    NORMAL = 0,
    RUNNING = 1,
    JUMPING = 2,
    INVICIBLE = 4
};

enum move
{
    LEFT,
    RIGHT,
    JUMP
};

struct vector2
{
    float x;
    float y;
};

struct Character
{
    enum status status;
    struct vector2 position;
    struct vector2 velocity;
    int health;
};

struct Character *init_player(void);

struct Character *init_enemy(struct vector2 position, int health);

void update_position(struct Character *character, float x, float y);

void delete_character(struct Character *character);
