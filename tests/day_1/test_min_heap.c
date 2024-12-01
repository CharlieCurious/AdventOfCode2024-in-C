#include <unity.h>
#include <min_heap.h>

void setUp(){
}

void test_should_create_heap_with_correct_initial_values() {
    MinHeap *heap = createMinHeap(3);

    TEST_ASSERT_EQUAL_UINT(3, heap->capacity);
    TEST_ASSERT_EQUAL_UINT(0, heap->size);
}

void tearDown() {
}

int main() {
    UNITY_BEGIN();
    RUN_TEST(test_should_create_heap_with_correct_initial_values);
    return UNITY_END();
}
