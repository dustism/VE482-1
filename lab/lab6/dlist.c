//
// Created by liu on 17-11-23.
//

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "dlist.h"
#include "list.h"

dlist createDlist(dlistValueType type) {
    if (type > DLIST_UNKOWN && type <= DLIST_DOUBLE) {
        list_t *list;
        list_init(&list);
        return list;
    }
    return NULL;
}

int dlistIsEmpty(dlist_const this) {
    return ((const list_t *) this)->length == 0;
}

void dlistAppend(dlist this, const char *key, dlistValue value) {
    char *str = malloc(strlen(key) + 1);
    strcpy(str, key);
    list_append(this, str, value);
}

void dlistSort(dlist_const this, dlist listDst, dlistSortMethod method) {




}

