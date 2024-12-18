#include <list_dict.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void free_key_value(KeyValue *kv);
static void free_locations_list(LocationList *list);
static size_t hash(char key, size_t capacity);
static KeyValue *kv_create(char key, Location location);
static bool location_list_insert(LocationList *location_list, Location location);

AnthenasDictionary *dictionary_create(size_t capacity) {
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

LocationList *dictionary_get(AnthenasDictionary *dict, char key) {
    if (!dict)
        return NULL;
    size_t index = hash(key, dict->capacity);
    
    KeyValue *kv = dict->kvp[index];
    while (kv) {
        if (kv->key == key) {
            return kv->value;
        }
        kv = kv->next;
    }

    return NULL;
}

void dictionary_get_all_kvp(AnthenasDictionary *dict, KeyValue *out_kvp, size_t *out_count) {
    *out_count = 0;
    for (size_t i = 0; i < dict->capacity; i++) {
        KeyValue *current = dict->kvp[i];
        while (current) {
            out_kvp[*out_count] = *current;
            (*out_count)++;
            current = current->next;
        }
    }
}

bool dictionary_insert(AnthenasDictionary *dict, char key, Location location) {
    if (!dict)
        return false;
    size_t index = hash(key, dict->capacity);

    KeyValue *kv = dict->kvp[index];
    while (kv) {
        if (kv->key == key) {
            LocationList *location_list = kv->value;
            return location_list_insert(location_list, location);
        }
        kv = kv->next;
    }

    KeyValue *new_kv = kv_create(key, location);
    if (!new_kv)
        return false;

    dict->kvp[index] = new_kv;
    
    return true;
}

void dictionary_free(AnthenasDictionary *dict) {
    if (!dict)
        return;

    for (size_t i = 0; i < dict->capacity; i++) {
        free_key_value(dict->kvp[i]);
    }
    free(dict);
}

bool location_equal(Location this, Location that) {
    return this.x == that.x && this.y == that.y;
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

static KeyValue *kv_create(char key, Location location) {
    KeyValue *kv = (KeyValue *)malloc(sizeof(KeyValue));
    if (!kv)
        return NULL;

    LocationList *location_list = (LocationList *)malloc(sizeof(LocationList));
    if (!location_list)
        goto free_kv;

    Location *locations = (Location *)calloc(INITIAL_MAX_LOCATIONS_PER_SYMBOL, sizeof(Location));
    if (!locations)
        goto free_location_list;

    locations[0] = location;
    location_list->size = 1;
    location_list->capacity = INITIAL_MAX_LOCATIONS_PER_SYMBOL;
    location_list->locations = locations;
    
    kv->key = key;
    kv->next = NULL;
    kv->value = location_list;

    return kv;

free_location_list:
    free(location_list);

free_kv:
    free(kv);

    perror("Malloc error when creating KeyValue");

    return NULL;
}


static bool location_list_insert(LocationList *location_list, Location location) {
    if (location_list->size == location_list->capacity) {
        size_t new_capacity = location_list->capacity * 2;

        LocationList *reallocd = realloc(location_list, new_capacity);
        if (!reallocd)
            return false;

        location_list = reallocd;
        location_list->capacity = new_capacity;
    }

    location_list->locations[location_list->size++] = location;
    return true;
}
