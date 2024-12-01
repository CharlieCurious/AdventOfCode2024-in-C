#include <min_heap.h>
#include <stdio.h>
#include <stdlib.h>

static void insert_ordered(MinHeap *heap, unsigned int index);
static void swap(unsigned int *a, unsigned int *b);
static void rebuild_heap(MinHeap *heap, unsigned int index);

MinHeap *create_min_heap(unsigned int capacity) {
    MinHeap *heap = (MinHeap *)malloc(sizeof(MinHeap));
    if (heap == NULL) return NULL;

    heap->data = (unsigned int *)calloc(capacity, sizeof(unsigned int));
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

void free_min_heap(MinHeap **heap) {
    if (heap != NULL && *heap != NULL) {
        if ((*heap)->data != NULL) {
            free((*heap)->data);
            (*heap)->data = NULL; 
        }
        free(*heap);
        *heap = NULL; 
    }
}

unsigned int pop_min(MinHeap *heap) {
    if (heap->size == 0) {
        perror("Heap is empty. Cannot pop min.");
        return NULL;
    }

    unsigned int min_value = heap->data[0];
    
    heap->data[0] = heap->data[heap->size - 1];
    heap->size--;
    
    rebuild_heap(heap, 0);

    return min_value;
}

static void insert_ordered(MinHeap *heap, unsigned int index) {
    unsigned int parent = (index - 1) / 2;

    if (index > 0 && heap->data[index] < heap->data[parent]) {
        swap(&heap->data[index], &heap->data[parent]);
        insert_ordered(heap, parent);
    }
}

static void rebuild_heap(MinHeap *heap, unsigned int index) {
    unsigned int left_child = 2 * index + 1;
    unsigned int right_child = 2 * index + 2;
    unsigned int smallest = index;

    if (left_child < heap->size && heap->data[left_child] < heap->data[smallest]) {
        smallest = left_child;
    }

    if (right_child < heap->size && heap->data[right_child] < heap->data[smallest]) {
        smallest = right_child;
    }

    if (smallest != index) {
        swap(&heap->data[index], &heap->data[smallest]);
        rebuild_heap(heap, smallest);
    }
}

static void swap(unsigned int *a, unsigned int *b) {
    *a = *a ^ *b;
    *b = *b ^ *a;
    *a = *a ^ *b;
}


