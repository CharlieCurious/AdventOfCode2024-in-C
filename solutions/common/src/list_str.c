#include <collections.h>
#include <string.h>

ListString *create_list_str(size_t capacity) {
    ListString *list = (ListString *)malloc(sizeof(ListString));
    char **strings = (char **)calloc(capacity, sizeof(char *));

    if (!list) {
        perror("Failed to allocate memory for ListString");
        return NULL;
    }

    list->strings = strings;
    list->capacity = capacity;
    list->size = 0;

    return list;
}

void append_list_str(ListString *list, char *string) {
    if (list == NULL || string == NULL) {
        perror("List or string is NULL");
        return;
    }

    if (list->size == list->capacity) {
        size_t new_capacity = list->capacity == 0 ? 1 : list->capacity * 2;
        char **new_strings = realloc(list->strings, new_capacity * sizeof(char *));
        if (new_strings == NULL) {
            perror("Failed to reallocate memory for strings");
            return;
        }

        list->strings = new_strings;
        list->capacity = new_capacity;
    }

    list->strings[list->size] = strdup(string);
    if (list->strings[list->size] == NULL) {
        perror("Failed to allocate memory for new string");
        return;
    }

    list->size++;
}

void free_list_str(ListString **list) {
    if (list == NULL || *list == NULL)
        return;

    if ((*list)->strings != NULL) {
        for (size_t i = 0; i < (*list)->size; i++) {
            if ((*list)->strings[i]) {
                free((*list)->strings[i]);
            }
        }
        free((*list)->strings);
        (*list)->strings = NULL;
    }

    free(*list);
    *list = NULL;
}
