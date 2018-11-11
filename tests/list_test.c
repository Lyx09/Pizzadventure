#include "list.h"

void print_list(struct list *list)
{
    while (list->next)
    {
        printf("%c ", list->b);
        list = list->next;
    }

    printf("%c\n", list->b);
}

int main(void)
{
    struct Block *block = malloc(sizeof(struct Block));

    if (!block)
        return 1;

    block->type = AIR;
    block->tilepos.x = .0;
    block->tilepos.y = .0;

    struct list *l0 = list_add(NULL, 'A', block);
    struct list *l1 = list_add(l0, 'B', block);
    struct list *l2 = list_add(l1, 'C', block);
    struct list *l3 = list_add(l2, 'D', block);
    struct list *l4 = list_add(l3, 'E', block);

    print_list(l4);

    destroy_list(l4);
}
