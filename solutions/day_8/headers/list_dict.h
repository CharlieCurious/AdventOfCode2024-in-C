#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#define INITIAL_MAX_LOCATIONS_PER_SYMBOL 10

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
    size_t capacity;
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

AnthenasDictionary *dictionary_create(size_t capacity);
LocationList *dictionary_get(AnthenasDictionary *dict, char key);
bool dictionary_insert(AnthenasDictionary *dict, char key, Location location);
void dictionary_free(AnthenasDictionary *dict);
bool location_equal(Location this, Location that);
