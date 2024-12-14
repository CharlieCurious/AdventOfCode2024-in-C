#include <list_dict.h>
#include <stdlib.h>

static void free_key_value(KeyValue *kv);
static void free_locations_list(LocationList *list);
static size_t hash(char key, size_t capacity);

AnthenasDictionary *dictionary_create(uint16_t capacity) {
    AnthenasDictionary *dict = (AnthenasDictionary *)malloc(sizeof(AnthenasDictionary));
    if (!dict) 
        goto return_null;

    KeyValue **kvp = (KeyValue **)calloc(capacity, sizeof(KeyValue *));
    if (!kvp)
        goto free_dictionary;
    
    dict->kvp = kvp;
    dict->capacity = capacity;
    return dict;

free_dictionary:
    free(dict);

return_null:
    return NULL;
}

bool dictionary_insert(AnthenasDictionary *dict, char key, Location location) {
    if (!dict)
        return false;

    KeyValue *kv = dict->kvp[hash(key, dict->capacity)];
    while (kv) {
        if (kv->key == key) {
            kv->value = location;
        }
    }
}

void dictionary_free(AnthenasDictionary *dict) {
    if (!dict)
        return;

    for (size_t i = 0; i < dict->capacity; i++) {
        free_key_value(dict->kvp[i]);
    }
    free(dict);
}

static void free_key_value(KeyValue *kv) {
    if (!kv)
        return;
    KeyValue *current = kv->next;
    while(current) {
        free_locations_list(current->value);
        free(current);
        current = current->next;
    }
    free(kv);
}

static void free_locations_list(LocationList *list) {
    if (!list)
        return;
    free(list);
}

static size_t hash(char key, size_t capacity) {
    return (key * 31) % capacity;
}
