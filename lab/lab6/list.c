//
// Created by liu on 17-11-25.
//

#include <stdlib.h>
#include <string.h>
#include "list.h"

// list iterators only used in this file

static void list_iter_next(list_iter_t *it) {
    node_t *next;
    if (it->b == it->list->zero) {
        next = it->list->first;
        it->flag = 1;
    } else {
        next = (node_t *) (it->b->pn ^ (size_t) it->a);
    }
    it->a = it->b;
    it->b = next;
}

static void list_iter_init(list_t *list, list_iter_t *it) {
    it->list = list;
    it->a = list->zero;
    it->b = list->first;
    it->flag = 0;
}

static int list_iter_end(list_iter_t *it) {
    return it->a == it->list->zero && it->flag;
}

static node_t *list_iter_get(list_iter_t *it) {
    return it->b;
}


void list_init(list_t **list) {
    *list = malloc(sizeof(list_t));
    node_t *temp = malloc(sizeof(node_t));
    temp->data = NULL;
    temp->str = NULL;
    temp->pn = 0;
    (*list)->zero = temp;
    (*list)->first = NULL;
    (*list)->last = NULL;
    (*list)->length = 0;
}

void list_free(list_t *list) {


}

node_t *list_prepend(list_t *list, char *str, dlistValue data) {
    node_t *new_node = malloc(sizeof(node_t));
    new_node->str = str;
    new_node->data = data;
    list->length++;
    if (list->first) {
        new_node->pn = (size_t) list->first;
        list->first->pn ^= (size_t) new_node;
    } else {
        new_node->pn = 0;
        list->last = new_node;
    }
    list->first = new_node;
    return new_node;
}

node_t *list_append(list_t *list, char *str, dlistValue data) {
    node_t *new_node = malloc(sizeof(node_t));
    new_node->str = str;
    new_node->data = data;
    list->length++;
    if (list->last) {
        new_node->pn = (size_t) list->last;
        list->last->pn ^= (size_t) new_node;
    } else {
        new_node->pn = 0;
        list->first = new_node;
    }
    list->last = new_node;
    return new_node;
}

list_t *list_sort(list_t *list, int (*cmp)(const void *, const void *)) {
    node_t *arr = malloc(sizeof(node_t) * list->length);
    list_iter_t it;
    int i = 0;
    for (list_iter_init(list, &it); list_iter_end(&it); list_iter_next(&it)) {
        memcpy(arr + (i++), list_iter_get(&it), sizeof(node_t));
    }
    qsort(arr, list->length, sizeof(node_t), cmp);
    list_t *new_list;
    list_init(&new_list);
    for (i = 0; i < list->length; ++i) {
        char *str = malloc(strlen(arr[i].str) + 1);
        strcpy(str, arr[i].str);
        list_append(new_list, str, arr[i].data);
    }
    free(arr);
}


