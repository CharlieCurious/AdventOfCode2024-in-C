#pragma once

// MinHeap for unsigned ints
typedef struct {
    unsigned int *data;
    unsigned int capacity;
    unsigned int size;
} MinHeap;

MinHeap *createMinHeap(unsigned int capacity);

void insert(MinHeap *heap, unsigned int value);
