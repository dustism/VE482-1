//
// Created by 38569 on 2017/10/15.
//

#ifndef PROJECT_LIST_H
#define PROJECT_LIST_H

#include <stdio.h>

typedef struct node {
    char *str;
    void *data;
    struct node *next;
} node_t;

typedef struct list {
    struct node *first;
    size_t length;
} list_t;

void list_init(list_t **list);

void list_free(list_t *list);

node_t *list_insert(list_t *list, node_t *node, char *str, void *data);

node_t *list_insert_first(list_t *list, char *str, void *data);

void list_sort(list_t *list, int (*cmp)(const void *, const void *));

void list_print(list_t *list, FILE *file, void(*print)(FILE* file, const void *));

#endif //PROJECT_LIST_H
