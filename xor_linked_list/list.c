//
// Created by liu on 17-11-23.
//

#include "list.h"

void list_init(list_t **list)
{
    *list = malloc(sizeof(list_t));
    node_t *temp = malloc(sizeof(node_t));
    temp->data = NULL;
    temp->str = NULL;
    temp->pn = NULL;
    (*list)->zero = temp;
    (*list)->start = NULL;
    (*list)->length = 0;
}

void list_free(list_t *list)
{


}

node_t *list_insert_first(list_t *list, char *str, void *data)
{
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

