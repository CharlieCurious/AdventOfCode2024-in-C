#pragma once

#include <stdbool.h>

typedef struct KeyValue {
    unsigned int key;
    unsigned int value;
    struct KeyValue *next;
} KeyValue;

typedef struct Dictionary{
    KeyValue **buckets;
    unsigned int capacity;
} Dictionary;

Dictionary *create_dictionary(unsigned int capacity);

bool insert_in_dictionary(Dictionary *dict, unsigned int key, unsigned int value);

bool find(Dictionary *dict, unsigned int key, unsigned int *value);
