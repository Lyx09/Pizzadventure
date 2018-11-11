#include "map.h"

void print_map(struct Map *map)
{
    struct Level *prev = map->prev;
    struct Level *next = map->next;

    printf("prev: %s (%f,%f)\n", prev->path, prev->coords.x, prev->coords.y);
    printf("next: %s (%f,%f)\n", next->path, next->coords.x, next->coords.y);
    printf("background: %s\n", map->background);
    printf("tileset: %s\n", map->tileset);
    printf("tilesize: (%f,%f)\n\n", map->tilesize.x, map->tilesize.y);

    for (int i = 0; i < MAP_WIDTH * MAP_HEIGHT; ++i)
    {
        if (i % MAP_WIDTH == 0 && i != 0)
            printf("\n");

        switch (map->blocks[i].type)
        {
            case EMPTY:
                printf("_");
                break;

            case OPEN:
                printf("O");
                break;

            case SOLID:
                printf("S");
                break;

            case HARMFUL:
                printf("H");
        }
    }

    printf("\n");
}

int main(int argc, char *argv[])
{
    if (argc != 2)
        return 1;

    struct Map *map = generate_map(argv[1]);

    print_map(map);
    destroy_map(map);

    return 0;
}
