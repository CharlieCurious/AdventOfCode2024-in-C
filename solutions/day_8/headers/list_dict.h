#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct Location {
    uint8_t x;
    uint8_t y;
} Location;

typedef struct AnthenaTuple {
    Location a;
    Location b;
} AnthenaTuple;

typedef struct LocationList {
    Location *locations;
    size_t size;
} LocationList;

typedef struct KeyValue {
    LocationList *value;
    struct KeyValue *next;
    char key;
} KeyValue;

typedef struct AnthenasDictionary {
    KeyValue **kvp;
    size_t capacity;
} AnthenasDictionary;

AnthenasDictionary *dictionary_create(uint16_t capacity);
bool dictionary_insert(AnthenasDictionary *dict, char symbol, Location location);
void dictionary_free(AnthenasDictionary *dict);
