#pragma once

// MinHeap for unsigned ints
typedef struct {
    unsigned int *data;
    unsigned int capacity;
    unsigned int size;
} MinHeap;

MinHeap *create_min_heap(unsigned int capacity);

void insert(MinHeap *heap, unsigned int value);

void free_min_heap(MinHeap **heap);

unsigned int pop_min(MinHeap *heap);
