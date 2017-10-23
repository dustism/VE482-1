//
// Created by liu on 2017/10/20.
//

#ifndef PROJECT_API_H
#define PROJECT_API_H

#include "list.h"

typedef enum {
    VAR_INT,
    VAR_DOUBLE,
    VAR_STRING,
    VAR_SIZE
} VAR_TYPE;

typedef enum {
    SORT_INC,
    SORT_DEC,
    SORT_RAND,
    SORT_SIZE
} SORT_TYPE;

static const char *TYPE_NAME[VAR_SIZE] = {
        "int.txt", "double.txt", "string.txt"
};

static const char *SORT_NAME[SORT_SIZE] = {
        "inc", "dec", "rand"
};

void generate_filename(char *buffer, VAR_TYPE var_type, SORT_TYPE sort_type);

VAR_TYPE get_var_type(const char *filename);

SORT_TYPE get_sort_type(const char* str);

void read_and_sort(VAR_TYPE var_type, SORT_TYPE sort_type);

#endif // PROJECT_API_H
