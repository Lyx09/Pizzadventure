#include "map.h"

static void set_block(struct Block *block, char type, float x, float y)
{
    switch (type)
    {
        case 'E':
            block->type = EMPTY;
            break;

        case 'O':
            block->type = OPEN;
            break;

        case 'S':
            block->type = SOLID;
            break;

        case 'H':
            block->type = HARMFUL;
            break;

        case 'N':
            block->type = NEXT;
            break;

        case 'P':
            block->type = PREV;
            break;

        default:
            block->type = OPEN;
    }

    block->tilepos.x = x;
    block->tilepos.y = y;
}

struct Map *generate_map(char *pathname)
{
    FILE *file = fopen(pathname, "r");

    if (!file)
        return NULL;

    struct Map *map = malloc(sizeof(struct Map));

    if (!map)
    {
        fclose(file);
        return NULL;
    }

    map->prev = malloc(sizeof(struct Level));
    map->next = malloc(sizeof(struct Level));

    if (!map->prev || !map->next)
    {
        destroy_map(map);
        fclose(file);
        return NULL;
    }

    struct Level *pv = map->prev;
    struct Level *nx = map->next;

    fscanf(file, "prev: %s (%f,%f)\n", pv->path, &pv->coords.x, &pv->coords.y);
    fscanf(file, "next: %s (%f,%f)\n", nx->path, &nx->coords.x, &nx->coords.y);
    fscanf(file, "music: %s\n", map->music);
    fscanf(file, "background: %s\n", map->background);
    fscanf(file, "tileset: %s\n", map->tileset);
    fscanf(file, "tilesize: (%f,%f)\n\n", &map->tilesize.x, &map->tilesize.y);

    int n;

    fscanf(file, "%d\n", &n);

    char block;
    char type;
    float tilepos_x;
    float tilepos_y;
    struct list *block_list = NULL;
    struct Block *tmp;

    for (int i = 0; i < n; ++i)
    {
        fscanf(file, "%c: %c(%f,%f)\n", &block, &type, &tilepos_x, &tilepos_y);
        tmp = malloc(sizeof(struct Block));

        if (!tmp)
        {
            destroy_map(map);
            fclose(file);
            return NULL;
        }

        set_block(tmp, type, tilepos_x, tilepos_y);
        block_list = list_add(block_list, block, tmp);
    }

    block = fgetc(file); // eats the '_'
    block = fgetc(file); // eats the '\n'
    map->blocks = malloc(MAP_WIDTH * MAP_HEIGHT * sizeof(struct Block));

    if (!map->blocks)
    {
        destroy_list(block_list);
        destroy_map(map);
        fclose(file);
        return NULL;
    }

    struct Block *b;

    for (int i = 0; i < MAP_WIDTH * MAP_HEIGHT; ++i)
    {
        block = fgetc(file);

        if (block == EOF)
            break;

        if (block == '\n')
        {
            block = fgetc(file);
        }

        if (block == ' ')
        {
            map->blocks[i].type = EMPTY;
            map->blocks[i].tilepos.x = .0;
            map->blocks[i].tilepos.y = .0;
            continue;
        }

        b = list_find(block_list, block);
        map->blocks[i].type = b->type;
        map->blocks[i].tilepos.x = b->tilepos.x;
        map->blocks[i].tilepos.y = b->tilepos.y;
    }

    destroy_list(block_list);
    fclose(file);

    return map;
}

void destroy_map(struct Map *map)
{
    free(map->prev);
    free(map->next);
    free(map->blocks);
    free(map);
}
