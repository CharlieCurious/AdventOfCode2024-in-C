#pragma once

#include <stdio.h>
#include <stdlib.h>

typedef struct ListString {
    char **strings;
    size_t size;
    size_t capacity;
} ListString;


ListString *create_list_str(size_t capacity);

void append_list_str(ListString *list, char *string);

void free_list_str(ListString **list);
