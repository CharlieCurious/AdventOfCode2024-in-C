#include <collections.h>

static size_t hash(uint key, size_t capacity);

HashSetUInt *create_hashset_uint(size_t initial_capacity) {
    HashSetUInt *set = (HashSetUInt *)malloc(sizeof(HashSetUInt));
    if (!set) {
        perror("Failed to allocate for HashSetUInt");
        return NULL;
    }

    set->buckets = (NodeUInt **)calloc(initial_capacity, sizeof(NodeUInt *));
    if (!set->buckets) {
        perror("Failed to allocate for HashSetUInt->buckets");
        return NULL;
    }

    set->size = 0;
    set->capacity = initial_capacity;
    return set;
}

bool insert_hashset_uint(HashSetUInt *set, uint value) {
    size_t index = hash(value, set->capacity);
    
    NodeUInt *current = set->buckets[index];
    while (current) {
        if (current->value == value) return false;
        current = current->next;
    }

    NodeUInt *new_node = (NodeUInt *)malloc(sizeof(NodeUInt));
    if (!new_node) {
        perror("Failed to allocate memory for new_node in hashset_uint");
        return false;
    }

    new_node->value = value;
    new_node->next = set->buckets[index];
    set->buckets[index] = new_node;
    set->size++;

    return true;
}

bool hashset_uint_contains(HashSetUInt *set, uint value) {
    size_t index = hash(value, set->capacity);

    NodeUInt *current = set->buckets[index];
    while (current) {
        if (current->value == value)
            return true;
        current = current->next;
    }

    return false;
}

void free_hashset_uint(HashSetUInt *set) {
    if (!set) return;

    for (size_t i = 0; i < set->capacity; i++) {
        NodeUInt *current = set->buckets[i];
        while(current) {
            NodeUInt *next = current->next;
            free(current);
            current = next;
        }
    }
    free(set->buckets);
    free(set);
    set = NULL;
}

static size_t hash(uint key, size_t capacity) {
    return (key * 31) % capacity;
}
