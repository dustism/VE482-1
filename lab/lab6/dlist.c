//
// Created by liu on 17-11-23.
//

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "dlist.h"
#include "list.h"

int int_inc(const void *a, const void *b) {
    int _a = ((node_t *) a)->data.intValue;
    int _b = ((node_t *) b)->data.intValue;
    if (_a > _b) return 1;
    if (_a < _b) return -1;
    return 0;
}

int int_dec(const void *a, const void *b) {
    return int_inc(b, a);
}

int double_inc(const void *a, const void *b) {
    double _a = ((node_t *) a)->data.doubleValue;
    double _b = ((node_t *) b)->data.doubleValue;
    if (_a > _b) return 1;
    if (_a < _b) return -1;
    return 0;
}

int double_dec(const void *a, const void *b) {
    return double_inc(b, a);
}

int string_inc(const void *a, const void *b) {
    return strcmp(((node_t *) a)->data.strValue, ((node_t *) b)->data.strValue);
}

int string_dec(const void *a, const void *b) {
    return strcmp(((node_t *) b)->data.strValue, ((node_t *) a)->data.strValue);
}

int all_rand(const void *a, const void *b) {
    return (rand() % 2) * 2 - 1;
}

int (*const cmp[3][3])(const void *, const void *) = {
        {all_rand, int_inc,    int_dec},
        {all_rand, string_inc, string_dec},
        {all_rand, double_inc, double_dec},
};

dlist createDlist(dlistValueType type) {
    if (type > DLIST_UNKOWN && type <= DLIST_DOUBLE) {
        list_t *list;
        list_init(&list);
        list->type = type;
        return list;
    }
    return NULL;
}

int dlistIsEmpty(dlist_const this) {
    return ((const list_t *) this)->length == 0;
}

void dlistAppend(dlist this, const char *key, dlistValue value) {
    list_append(this, key, value);
}

void dlistSort(dlist_const this, dlist listDst, dlistSortMethod method) {
    list_clear(listDst);
    dlistValueType type = ((const list_t *) (this))->type;
    if (type <= DLIST_UNKOWN || type > DLIST_DOUBLE) {
        return;
    }
    if (method <= DLIST_SORT_UNKOWN || method > DLIST_SORT_DEC) {
        return;
    }
    list_sort(this, listDst, cmp[type - 1][method - 1]);
}

void dlistPrint(dlist_const this) {
    list_print(this, stdout);
}

void dlistFree(dlist this) {
    list_free(this);
}
