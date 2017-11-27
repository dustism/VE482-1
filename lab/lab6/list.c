//
// Created by liu on 17-11-25.
//

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "list.h"

// list iterators only used in this file

static void list_iter_next(list_iter_t *it) {
    node_t *next;
    if (it->b == it->list->last) {
        next = it->list->zero;
    } else if (it->a == it->list->zero) {
        next = (node_t *) (it->b->pn);
    } else {
        next = (node_t *) (it->b->pn ^ (size_t) it->a);
    }
    it->a = it->b;
    it->b = next;
}

static void list_iter_init(const list_t *list, list_iter_t *it) {
    it->list = list;
    it->a = list->zero;
    it->b = list->first;
}

static int list_iter_end(list_iter_t *it) {
    return it->b == it->list->zero || it->list->length == 0;
}

static node_t *list_iter_get(list_iter_t *it) {
    return it->b;
}


node_t *list_node_init(list_t *list, const char *str, dlistValue data) {
    node_t *new_node = malloc(sizeof(node_t));
    char *key = malloc(strlen(str) + 1);
    strcpy(key, str);
    new_node->str = key;
    if (list->type == DLIST_STR) {
        char *str_data = malloc(strlen(data.strValue) + 1);
        strcpy(str_data, data.strValue);
        new_node->data.strValue = str_data;
    } else {
        new_node->data = data;
    }
    return new_node;
}

void list_node_free(list_t *list, node_t *node) {
    if (list->type == DLIST_STR) {
        free(node->data.strValue);
    }
    free(node->str);
    free(node);
}

void list_init(list_t **list) {
    *list = malloc(sizeof(list_t));
    node_t *temp = malloc(sizeof(node_t));
    temp->str = NULL;
    temp->pn = 0;
    (*list)->zero = temp;
    (*list)->first = NULL;
    (*list)->last = NULL;
    (*list)->length = 0;
}

void list_free(list_t *list) {
    list_clear(list);
    free(list->zero);
    free(list);
}

void list_clear(list_t *list) {
    list_iter_t it;
    for (list_iter_init(list, &it); !list_iter_end(&it); list_iter_next(&it)) {
        node_t *temp = list_iter_get(&it);
        list_node_free(list, temp);
    }
    list->first = list->last = NULL;
    list->length = 0;
}


node_t *list_prepend(list_t *list, const char *str, dlistValue data) {
    node_t *new_node = list_node_init(list, str, data);
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

node_t *list_append(list_t *list, const char *str, dlistValue data) {
    node_t *new_node = list_node_init(list, str, data);
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

void list_sort(list_t *list, list_t *new_list, int (*cmp)(const void *, const void *)) {
    node_t *arr = malloc(sizeof(node_t) * list->length);
    list_iter_t it;
    int i = 0;
    for (list_iter_init(list, &it); !list_iter_end(&it); list_iter_next(&it)) {
        memcpy(arr + (i++), list_iter_get(&it), sizeof(node_t));
    }
    qsort(arr, list->length, sizeof(node_t), cmp);
    for (i = 0; i < list->length; ++i) {
        list_append(new_list, arr[i].str, arr[i].data);
    }
    free(arr);
}

void list_print(const list_t *list, FILE *file) {
    list_iter_t it;
    for (list_iter_init(list, &it); !list_iter_end(&it); list_iter_next(&it)) {
        node_t *temp = list_iter_get(&it);
        fprintf(file, "%s=", temp->str);
        switch (list->type) {
        case DLIST_STR:
            fprintf(file, "%s\n", temp->data.strValue);
            break;
        case DLIST_INT:
            fprintf(file, "%d\n", temp->data.intValue);
            break;
        case DLIST_DOUBLE:
            fprintf(file, "%lf", temp->data.doubleValue);
            break;
        default:
            assert(0);
        }
    }
}

