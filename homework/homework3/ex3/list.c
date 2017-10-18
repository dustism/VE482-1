//
// Created by 38569 on 2017/10/15.
//

#include <stdlib.h>
#include <string.h>
#include "list.h"

void list_init(list_t **list) {
    *list = malloc(sizeof(list_t));
    (*list)->first = NULL;
    (*list)->length = 0;
}

void list_free(list_t *list) {
    node_t *temp = list->first;
    for (int i = 0; i < list->length; i++) {
        temp = temp->next;
        free(list->first->str);
        free(list->first->data);
        free(list->first);
        list->first = temp;
    }
    free(list);
}

node_t *list_insert(list_t *list, node_t *node, char *str, void *data) {
    node_t *new_node = malloc(sizeof(node_t));
    new_node->str = str;
    new_node->data = data;
    list->length++;
    new_node->next = node->next;
    node->next = new_node;
    return new_node;
}

node_t *list_insert_first(list_t *list, char *str, void *data) {
    node_t *new_node = malloc(sizeof(node_t));
    new_node->str = str;
    new_node->data = data;
    list->length++;
    if (list->first) {
        new_node->next = list->first;
    } else {
        new_node->next = NULL;
    }
    list->first = new_node;
    return new_node;
}

const node_t *list_search(list_t *list, const node_t *first, const void *data, int (*cmp)(const void *, const void *)) {
    if (list->first == NULL) return NULL;
    if (first == NULL) first = list->first;
    else first = first->next;
    while (first) {
        if (cmp(first->data, data)) return first;
        first = first->next;
    }
    return first;
}

void list_sort(list_t *list, int (*cmp)(const void *, const void *)) {
    if (list->length == 0)return;
    node_t *arr = malloc(sizeof(node_t) * list->length);
    node_t *temp = list->first;
    for (size_t i = 0; i < list->length; i++) {
        memcpy(arr + i, temp, sizeof(node_t));
        temp = temp->next;
    }
    qsort(arr, list->length, sizeof(node_t), cmp);
    temp = list->first;
    for (size_t i = 0; i < list->length; i++) {
        temp->str = arr[i].str;
        temp->data = arr[i].data;
        temp = temp->next;
    }
    free(arr);
}

void list_print(const list_t *list, FILE *file, void(*print)(FILE *file, const void *)) {
    node_t *temp = list->first;
    for (size_t i = 0; i < list->length; i++) {
        fprintf(file, "%s=", temp->str);
        print(file, temp->data);
        fprintf(file, "\n");
        temp = temp->next;
    }
}
