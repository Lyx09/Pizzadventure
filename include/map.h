#ifndef MAP_H
#define MAP_H

#include <stdio.h>
#include <stdlib.h>
#include "character.h"
#include "list.h"

#define MAX_INPUT_SIZE 4096
#define MAP_WIDTH 40
#define MAP_HEIGHT 30

struct Level
{
    char path[MAX_INPUT_SIZE];
    struct vector2 coords;
};

enum type
{
    EMPTY = 0,
    OPEN,
    SOLID,
    HARMFUL
};

struct Block
{
    enum type type;
    struct vector2 tilepos;
};

struct Map
{
    struct Level *prev;
    struct Level *next;
    char music[MAX_INPUT_SIZE];
    char background[MAX_INPUT_SIZE];
    char tileset[MAX_INPUT_SIZE];
    struct vector2 tilesize;
    struct Block *blocks;
};

struct Map *generate_map(char *pathname);

void destroy_map(struct Map *map);

#endif /* !MAP_H */
