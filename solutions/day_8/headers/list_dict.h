#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#define INITIAL_MAX_LOCATIONS_PER_SYMBOL 1000
#define INITIAL_MAX_ANTINODE_LOCATIONS 1000

typedef struct Location {
    int x;
    int y;
} Location;

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

typedef struct AntinodeBucket {
    Location value;
    struct AntinodeBucket *next;
} AntinodeBucket;

typedef struct AntinodeSet {
    AntinodeBucket **nodes;
    size_t size;
    size_t capacity;
} AntinodeSet;

AnthenasDictionary *dictionary_create(size_t capacity);
LocationList *dictionary_get(AnthenasDictionary *dict, char key);
void dictionary_get_all_kvp(AnthenasDictionary *dict, KeyValue *out_kvp, size_t *out_count);
bool dictionary_insert(AnthenasDictionary *dict, char key, Location location);
void dictionary_free(AnthenasDictionary *dict);
bool location_equal(Location this, Location that);

AntinodeSet *antinode_set_create(size_t capacity);
bool antinode_set_insert(AntinodeSet *set, Location antinode);
void antinode_set_free(AntinodeSet *set);
size_t antinode_hash(Location antinode);
