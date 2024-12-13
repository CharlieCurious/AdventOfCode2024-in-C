#pragma once

#include <stdbool.h>
#include <stdint.h>

// 2 bytes
typedef struct Location {
    uint8_t x;
    uint8_t y;
} Location;

// 4 bytes
typedef struct AnthenaTuple {
    Location a;
    Location b;
} AnthenaTuple;

// 2 bytes + 8 bytes = 10 bytes.
// But padding will be added to make it 16 bytes to align.
typedef struct LocationList {
    Location *locations;
    uint16_t size;
} LocationList;

// 1 byte + 8 bytes + 8 bytes = 17 bytes
// But key will be padded to 8 bytes. So total is 24 bytes
typedef struct KeyValue {
    LocationList *value;
    struct KeyValue *next;
    char key;
} KeyValue;

// 2 bytes + 8 bytes = 10 bytes
// padding will make it 16 bytes
typedef struct AnthenasDictionary {
    KeyValue **kvp;
    uint16_t capacity;
} AnthenasDictionary;

AnthenasDictionary *dictionary_create(uint16_t capacity);
bool dictionary_insert(char symbol, Location location);
void dictionary_free(AnthenasDictionary *dict);
