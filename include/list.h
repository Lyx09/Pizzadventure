#ifndef LIST_H
#define LIST_H

#include <stddef.h>
#include "map.h"

struct list
{
    char b;
    struct Block *block;
    struct list *next;
};

struct list *list_add(struct list *list, char b, struct Block *block);

struct Block *list_find(struct list *list, char block);

void destroy_list(struct list *list);

#endif /* !LIST_H */
