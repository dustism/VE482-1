//
// Created by liu on 2017/10/20.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "interface.h"
#include "api.h"

int dispatch_cli(int argc, char *argv[]) {
    srand(time(NULL));
    if (argc < 3)return 0;
    VAR_TYPE var_type = get_var_type(argv[1]);
    SORT_TYPE sort_type = get_sort_type(argv[2]);
    if (var_type < VAR_SIZE && sort_type < SORT_SIZE) {
        read_and_sort(var_type, sort_type);
    }
    return 0;
}

int dispatch_ui(int argc, char *argv[]) {
    srand(time(NULL));
    char buffer[1000];
    printf("Welcome to the menu interface!\n");
    int exit_flag = 0;
    while (!exit_flag) {
        VAR_TYPE var_type = VAR_SIZE;
        SORT_TYPE sort_type = SORT_SIZE;
        printf("Please input one of the strings:\n");
        printf("- rand_int.txt (read random integers)\n");
        printf("- rand_double.txt (read random doubles)\n");
        printf("- rand_string.txt (read random strings)\n");
        printf("- exit (exit the program)\n");
        while (var_type == VAR_SIZE) {
            printf("> ");
            fgets(buffer, 999, stdin);
            buffer[strlen(buffer) - 1] = '\0';
            if (strcmp(buffer, "exit") == 0) {
                exit_flag = 1;
                break;
            }
            var_type = get_var_type(buffer);
            if (var_type == VAR_SIZE) {
                printf("Invalid input, please retry!\n");
            }
        }
        if (exit_flag) break;
        printf("Please input one of the strings:\n");
        printf("- inc (output in increasing order)\n");
        printf("- dec (output in decreasing order)\n");
        printf("- rand (output in random order)\n");
        printf("- exit (exit the program)\n");
        while (sort_type == SORT_SIZE) {
            printf("> ");
            fgets(buffer, 999, stdin);
            buffer[strlen(buffer) - 1] = '\0';
            if (strcmp(buffer, "exit") == 0) {
                exit_flag = 1;
                break;
            }
            sort_type = get_sort_type(buffer);
            if (sort_type == SORT_SIZE) {
                printf("Invalid input, please retry!\n");
            }
        }
        if (exit_flag) break;
        read_and_sort(var_type, sort_type);
        printf("The operation is successful!\n\n");
    }
    return 0;
}
