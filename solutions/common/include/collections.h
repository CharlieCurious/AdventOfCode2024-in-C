#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

typedef struct ListString {
    char **strings;
    size_t size;
    size_t capacity;
} ListString;

typedef struct ListUInt {
    uint *uints;
    size_t size;
    size_t capacity;
} ListUInt;


ListString *create_list_str(size_t capacity);

void append_list_str(ListString *list, char *string);

void free_list_str(ListString **list);

ListUInt *create_list_uint(size_t capacity);

void append_list_uint(ListUInt *list, uint uints);

void free_list_uint(ListUInt **list);
