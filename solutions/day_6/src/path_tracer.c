#include <path_tracer.h>
#include <stdlib.h>

static size_t hash(Step key, size_t capacity);
static bool step_equals(Step this, Step that);
static void resize(HashSet * set);

HashSet *hashset_create(size_t initial_capacity) {
    HashSet *set = (HashSet *)malloc(sizeof(HashSet));
    set->size = 0;
    set->capacity = initial_capacity;
    set->nodes = (Node **)calloc(initial_capacity, sizeof(Node *));
    return set;
}

bool hashset_insert(HashSet *set, Step value) {
    if (set->size == set->capacity)
        resize(set);

    size_t index = hash(value, set->capacity);

    Node *current = set->nodes[index];
    while(current) {
        if (step_equals(current->value, value))
            return false;
        current = current->next;
    }

    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->value = value;
    new_node->next = set->nodes[index];
    set->nodes[index] = new_node;
    set->size++;

    return true;
}

static void resize(HashSet * set) {
    size_t new_capaciity = set->capacity * 2;
    Node ** new_nodes = (Node **)calloc(new_capaciity, sizeof(Node *));

    for (size_t i = 0; i < set->capacity; i++) {
        Node *current = set->nodes[i];
        while (current) {
            size_t new_index = hash(current->value, new_capaciity);
            Node *new_node = (Node *)malloc(sizeof(Node));
            new_node->value = current->value;
            new_node->next = new_nodes[new_index];
            new_nodes[new_index] = new_node;
            current = current->next;
        }
    }

    free(set->nodes);

    set->nodes = new_nodes;
    set->capacity = new_capaciity;
}

void hashset_free(HashSet *set) {
    if (!set)
        return;

    for (size_t i = 0; i < set->size; i++) {
        Node *current = set->nodes[i];
        while (current) {
            Node *next = current->next;
            free(current);
            current = next;
        }
    }

    free(set->nodes);
    free(set);
}

static size_t hash(Step key, size_t capacity) {
    return ((key.x + key.y + key.direction) * 31) % capacity;
}

static bool step_equals(Step this, Step that) {
    return (this.direction == that.direction) &&
        (this.x == that.x) &&
        (this.y == that.y);
}
