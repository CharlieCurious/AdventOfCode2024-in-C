#include <dictionary.h>
#include <stdlib.h>

static unsigned int hash(unsigned int key, unsigned int capacity);

Dictionary *create_dictionary(unsigned int capacity) {
    Dictionary *dict = (Dictionary *)malloc(sizeof(Dictionary));
    if (!dict) return NULL;

    dict->buckets = (KeyValue **)calloc(capacity, sizeof(KeyValue *));
    if (!dict->buckets) {
        free(dict);
        return NULL;
    }

    dict->capacity = capacity;
    return dict;
}

bool insert_in_dictionary(Dictionary *dict, unsigned int key, unsigned int value) {
    if (!dict) return false;

    unsigned int index = hash(key, dict->capacity);
    KeyValue *pair = dict->buckets[index];

    // Check if the key should be updated
    while(pair) {
        if (pair->key == key) {
            pair->value = value;
            return true;
        }
        pair = pair->next;
    }
    
    KeyValue *new_pair = (KeyValue *)malloc(sizeof(KeyValue));
    if (!new_pair) return false;

    new_pair->key = key;
    new_pair->value = value;
    new_pair->next = dict->buckets[index];

    dict->buckets[index] = new_pair;
    return true;

}

bool find(Dictionary *dict, unsigned int key, unsigned int *value) {
    if (!dict) return false;

    unsigned int index = hash(key, dict->capacity);
    KeyValue *pair = dict->buckets[index];

    while (pair) {
        if (pair->key == key) {
            if (value) *value = pair->value;
            return true;
        }
        pair = pair->next;
    }

    return false; // Key not found
}

static unsigned int hash(unsigned int key, unsigned int capacity) {
    return (key * 31) % capacity;    
}













