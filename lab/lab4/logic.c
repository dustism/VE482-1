//
// Created by liu on 2017/10/20.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include "logic.h"

int int_inc(const void *a, const void *b) {
    int _a = *(int *) (((node_t *) a)->data);
    int _b = *(int *) (((node_t *) b)->data);
    if (_a > _b)return 1;
    if (_a < _b)return -1;
    return 0;
}

int int_dec(const void *a, const void *b) {
    return int_inc(b, a);
}

int double_inc(const void *a, const void *b) {
    double _a = *(double *) (((node_t *) a)->data);
    double _b = *(double *) (((node_t *) b)->data);
    if (_a > _b)return 1;
    if (_a < _b)return -1;
    return 0;
}

int double_dec(const void *a, const void *b) {
    return double_inc(b, a);
}

int string_inc(const void *a, const void *b) {
    return strcmp((char *) (((node_t *) a)->data), (char *) (((node_t *) b)->data));
}

int string_dec(const void *a, const void *b) {
    return strcmp((char *) (((node_t *) b)->data), (char *) (((node_t *) a)->data));
}

int all_rand(const void *a, const void *b) {
    return (rand() % 2) * 2 - 1;
}

int (*const cmp[VAR_SIZE][SORT_SIZE])(const void *, const void *) = {
        {int_inc,    int_dec,    all_rand},
        {double_inc, double_dec, all_rand},
        {string_inc, string_dec, all_rand}
};

void int_print(FILE *file, const void *a) {
    fprintf(file, "%d", *(int *) (a));
}

void double_print(FILE *file, const void *a) {
    fprintf(file, "%lf", *(double *) (a));
}

void string_print(FILE *file, const void *a) {
    fprintf(file, "%s", (char *) (a));
}

void (*const print[VAR_SIZE])(FILE *file, const void *) = {
        int_print, double_print, string_print
};

void generate_filename(char *buffer, VAR_TYPE var_type, SORT_TYPE sort_type) {
    strcpy(buffer, SORT_NAME[sort_type]);
    size_t length = strlen(buffer);
    buffer[length] = '_';
    strcpy(buffer + length + 1, TYPE_NAME[var_type]);
}

VAR_TYPE get_var_type(const char *filename) {
    char buffer[100] = {};
    VAR_TYPE var_type = 0;
    for (; var_type < VAR_SIZE; var_type++) {
        generate_filename(buffer, var_type, SORT_RAND);
        if (strcmp(buffer, filename) == 0) {
            break;
        }
    }
    return var_type;
}

SORT_TYPE get_sort_type(const char *str) {
    SORT_TYPE sort_type = 0;
    for (; sort_type < SORT_SIZE; sort_type++) {
        if (strcmp(SORT_NAME[sort_type], str) == 0) {
            break;
        }
    }
    return sort_type;
}

void read_and_sort(VAR_TYPE var_type, SORT_TYPE sort_type) {
    char filename[20] = {0};
    generate_filename(filename, var_type, SORT_RAND);
    FILE *input = fopen(filename, "r");
    if (!input) return;
    printf("reading %s\n", filename);
    char buffer[1024] = {0};
    list_t *list1;
    list_init(&list1);
    while (!feof(input)) {
        fgets(buffer, 1024, input);
        char *pos = strchr(buffer, '=');
        if (!pos) continue;
        size_t length = pos - buffer;
        *pos = '\0';
        char *str = (char *) malloc(sizeof(char) * (length + 1));
        strcpy(str, buffer);
        void *data;
        switch (var_type) {
        case VAR_INT:
            data = malloc(sizeof(int));
            *((int *) data) = strtol(pos + 1, NULL, 10);
            break;
        case VAR_DOUBLE:
            data = malloc(sizeof(double));
            *((double *) data) = strtod(pos + 1, NULL);
            break;
        case VAR_STRING:
            length = strlen(pos + 1);
            data = malloc(sizeof(char) * (length + 1));
            strcpy(data, pos + 1);
            pos = data + strlen(data) - 1;
            while (*pos == '\n') *(pos--) = '\0';
            break;
        default:
            assert(0);
            break;
        }
        list_insert_first(list1, str, data);
    }
    fclose(input);

    printf("sorting elements\n");
    list_sort(list1, cmp[var_type][sort_type]);

    generate_filename(filename, var_type, sort_type);
    printf("writing %s\n", filename);
    FILE *output = fopen(filename, "w");
    list_print(list1, output, print[var_type]);
    fclose(output);
    list_free(list1);
}
