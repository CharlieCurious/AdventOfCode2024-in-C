#include <list_dict.h>
#include <stdlib.h>

static bool resize(AntinodeSet *set) {
    size_t new_capacity = set->capacity == 0 ? 1 : set->capacity * 2;
    AntinodeBucket **new_nodes = (AntinodeBucket **)calloc(new_capacity, sizeof(AntinodeBucket *));
    if (!new_nodes)
        return false;

    for (size_t i = 0; i < set->capacity; i++) {
        AntinodeBucket *current = set->nodes[i];
        while (current) {
            AntinodeBucket *next = current->next;
            size_t new_index = antinode_hash(current->value) % new_capacity;
            current->next = new_nodes[new_index];
            new_nodes[new_index] = current;

            current = next;
        }
    }

    free(set->nodes);
    set->nodes = new_nodes;
    set->capacity = new_capacity;

    return true;
}

AntinodeSet *antinode_set_create(size_t capacity) {
    AntinodeSet *set = (AntinodeSet *)malloc(sizeof(AntinodeSet));
    if (!set)
        return NULL;

    AntinodeBucket **buckets = (AntinodeBucket **)calloc(capacity, sizeof(AntinodeBucket));
    if (!buckets) {
        free(set);
        return NULL;
    }

    set->capacity = capacity;
    set->size = 0;
    set->nodes = buckets;

    return set;
}

bool antinode_set_insert(AntinodeSet *set, Location antinode) {
    if (set->size == set->capacity) {
        bool resize_result = resize(set);
        if (!resize_result)
            return false;
    }

    size_t index = antinode_hash(antinode) % set->capacity;

    AntinodeBucket *current = set->nodes[index];
    while(current) {
        if (location_equal(antinode, current->value))
            return false;
        current = current->next;
    }

    AntinodeBucket *new_node = (AntinodeBucket *)malloc(sizeof(AntinodeBucket));
    if (!new_node)
        return false;

    new_node->value = antinode;
    new_node->next = set->nodes[index];
    set->nodes[index] = new_node;
    set->size++;

    return true;
}

void antinode_set_free(AntinodeSet *set) {
    if (!set)
        return;

    for (size_t i = 0; i < set->capacity; i++) {
        AntinodeBucket *current = set->nodes[i];
        while (current) {
            AntinodeBucket *next = current->next;
            free(current);
            current = next;
        }
    }

    free(set->nodes);
    free(set);
}

size_t antinode_hash(Location antinode) { 
    return (antinode.x + antinode.y) * 31; 
}
