#include <min_heap.h>
#include <stdio.h>
#include <stdlib.h>

static void insert_ordered(MinHeap *heap, unsigned int index);
static void swap(unsigned int *a, unsigned int *b);

MinHeap *createMinHeap(unsigned int capacity) {
    MinHeap *heap = (MinHeap *)malloc(sizeof(MinHeap));
    if (heap == NULL) return NULL;

    heap->data = (unsigned int*)malloc(capacity * sizeof(unsigned int));
    if (heap->data == NULL) return NULL;

    heap->capacity = capacity;
    heap->size = 0;

    return heap;
}

void insert(MinHeap *heap, unsigned int value) {
    if (heap->size == heap->capacity) {
        perror("Failed to insert value in heap. Heap is full.");
        return;
    }

    // Start by inserting at the end;
    heap->data[heap->size] = value;

    // Re-order heap O(nlog(n))
    insert_ordered(heap, heap->size);

    heap->size++;
}

static void insert_ordered(MinHeap *heap, unsigned int index) {
    unsigned int parent = (index - 1) / 2;

    if (index > 0 && heap->data[index] < heap->data[parent]) {
        swap(&heap->data[index], &heap->data[parent]);
        insert_ordered(heap, parent);
    }
}

static void swap(unsigned int *a, unsigned int *b) {
    *a = *a ^ *b;
    *b = *b ^ *a;
    *a = *a ^ *b;
}


