#include <stdio.h>
#include <stdlib.h>
#include "list.h"

struct list *list_add(struct list *list, char b, struct Block *block)
{
    struct list *head = malloc(sizeof(struct list));

    if (!head)
        return NULL;

    head->b = b;
    head->block = malloc(sizeof(struct Block));
    head->block->type = block->type;
    head->block->tilepos.x = block->tilepos.x;
    head->block->tilepos.y = block->tilepos.y;
    head->next = list;

    return head;
}

struct Block *list_find(struct list *list, char block)
{
    while (list && list->b != block)
        list = list->next;

    return list && list->b == block ? list->block : NULL;
}

void destroy_list(struct list *list)
{
    if (!list)
        return;

    destroy_list(list->next);
    free(list->block);
    free(list);
}
