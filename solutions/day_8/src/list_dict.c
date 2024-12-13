#include <list_dict.h>
#include <stdlib.h>

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

bool dictionary_insert(char symbol, Location location);

void dictionary_free(AnthenasDictionary *dict) {
    for (uint16_t i = 0; i < dict->capacity; i++) {
        if (dict->kvp[i]) {
            for 
        }
    }
}
