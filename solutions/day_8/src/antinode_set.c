#include <list_dict.h>
#include <stdlib.h>

static size_t hash(Antinode antinode, size_t capacity) {
    return ((antinode.a.x + antinode.b.x + antinode.a.y + antinode.b.y) * 31) % capacity;
}

static bool equal(Antinode this, Antinode that) {
    return this.a.x == that.a.x && this.a.y == that.a.y &&
        this.b.x == that.b.x && this.b.y == that.b.y;
}

static bool resize(AntinodeSet *set) {
    size_t new_capacity = set->capacity * 2;
    AntinodeSet *new_set = realloc(set, new_capacity);
    if (!new_set)
        return false;
    set = new_set;
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

bool antinode_set_insert(AntinodeSet *set, Antinode antinode) {
    if (set->size == set->capacity) {
        bool resize_result = resize(set);
        if (!resize_result)
            return false;
    }

    size_t index = hash(antinode, set->capacity);

    AntinodeBucket *current = set->nodes[index];
    while(current) {
        if (equal(antinode, current->value))
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
