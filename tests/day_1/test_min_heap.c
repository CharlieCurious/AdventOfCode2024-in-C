#include <unity.h>
#include <min_heap.h>

const unsigned int test_heap_capacity = 5;

MinHeap *test_heap = NULL;

void setUp(){
    test_heap = create_min_heap(test_heap_capacity);
}

void test_should_create_heap_with_correct_initial_values() {
    TEST_ASSERT_EQUAL_UINT(test_heap_capacity, test_heap->capacity);
    TEST_ASSERT_EQUAL_UINT(0, test_heap->size);
}

void test_should_be_ordered() {
    unsigned int data[5] = { 3, 2, 4, 5, 1};
    unsigned int expected_order[5] = { 1, 2, 3, 4, 5 };
    unsigned int result[5];

    for (unsigned int i = 0; i < 5; i++) {
        insert(test_heap, data[i]);
    }

    for (unsigned int i = 0; i < 5; i++) {
        result[i] = pop_min(test_heap);
    }

    TEST_ASSERT_EQUAL_UINT_ARRAY(expected_order, result, 5);
}

void test_should_free_heap() {

    free_min_heap(&test_heap);

    TEST_ASSERT_NULL(test_heap);
}

void tearDown() {
    free_min_heap(&test_heap);
}

int main() {
    UNITY_BEGIN();
    RUN_TEST(test_should_create_heap_with_correct_initial_values);
    RUN_TEST(test_should_be_ordered);
    RUN_TEST(test_should_free_heap);
    return UNITY_END();
}
