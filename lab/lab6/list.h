//
// Created by liu on 17-11-25.
//

#ifndef PROJECT_LIST_H
#define PROJECT_LIST_H

#include <stddef.h>
#include "dlist.h"

typedef struct node {
    char *str;
    dlistValue data;
    size_t pn;
} node_t;

typedef struct list {
    struct node *zero, *first, *last;
    size_t length;
    dlistValueType type;
} list_t;

typedef struct list_iter {
    struct list* list;
    struct node *a, *b;
    int flag;
} list_iter_t;

void list_init(list_t **list);

void list_free(list_t *list);

node_t *list_prepend(list_t *list, char *str, dlistValue data);

node_t *list_append(list_t *list, char *str, dlistValue data);

list_t *list_sort(list_t *list, int (*cmp)(const void *, const void *));


//void list_iter_prev(list_iter_t *it);

//void list_print(const list_t *list, FILE *file, void(*print)(FILE* file, const void *));

#endif //PROJECT_LIST_H
