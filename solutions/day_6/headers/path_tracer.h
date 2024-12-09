#pragma once

#include <stddef.h>
#include <stdbool.h>

typedef enum Direction {
    NORTH,
    SOUTH,
    EAST,
    WEST
} Direction;

typedef struct Step {
    size_t x;
    size_t y;
    Direction direction;
} Step;

typedef struct Node {
    Step value;
    struct Node *next;
} Node;

typedef struct HashSet {
    Node **nodes;
    size_t size;
    size_t capacity;
} HashSet;

Step step_create(size_t current_x, size_t current_y, Direction direction);
HashSet *hashset_create(size_t initial_capacity);
bool hashset_insert(HashSet *set, Step value);
void hashset_free(HashSet *set);


