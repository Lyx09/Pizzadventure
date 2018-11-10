enum status
{
    NORMAL = 0,
    RUNNING = 1,
    JUMPING = 2,
    INVICIBLE = 4
}

struct vector2
{
    float x;
    float y;
};

struct player
{
    enum status status;
    struct vector2 position;
};
