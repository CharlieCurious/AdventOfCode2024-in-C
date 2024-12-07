#include <collections.h>

  
ListUInt *create_list_uint(size_t initial_capacity) {
    ListUInt *list = (ListUInt *)malloc(sizeof(ListUInt));
    uint *nums = (uint *)calloc(initial_capacity, sizeof(uint));

    if(!list || !nums) {
        perror("Failed to allocate memory for ListUint");
        return NULL;
    }

    list->uints = nums;
    list->capacity = initial_capacity;
    list->size = 0;

    return list;
}

void append_list_uint(ListUInt *list, uint number) {
    if (list == NULL) {
        return;
    }

    if (list ->size == list->capacity) {
        size_t new_capacity = list->capacity == 0 ? 1 : list->capacity * 2;
        uint *new_storage = realloc(list->uints, new_capacity * sizeof(uint));
        if (!new_storage) {
            perror("Failed to reallocate memory for ListUInt");
            return;
        }

        list->uints = new_storage;
        list->capacity = new_capacity;
    }

    list->uints[list->size] = number;
    list->size++;
}

void free_list_uint(ListUInt **list) {
    if (list == NULL || *list == NULL)
        return;

    if ((*list)->uints != NULL) {
        free((*list)->uints);
        (*list)->uints = NULL;
    }

    free(*list);
    *list = NULL;
}

