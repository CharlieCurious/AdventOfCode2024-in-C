#include "unity_internals.h"
#include <collections.h>
#include <unity.h>

HashSetUInt *set;

void setUp() {
}

void should_create_with_correct_data() {
    set = create_hashset_uint(3);

    TEST_ASSERT_EQUAL_size_t(3, set->capacity);
    TEST_ASSERT_EQUAL_size_t(0, set->size);
}

void should_insert_value() {
    set = create_hashset_uint(1);

    bool result = insert_hashset_uint(set, 3);

    TEST_ASSERT_EQUAL_size_t(1, set->size);
    TEST_ASSERT_TRUE(result);
    TEST_ASSERT_TRUE(hashset_uint_contains(set, 3));
}


void tearDown() {
    free_hashset_uint(set);
}

int main() {
    UNITY_BEGIN();
    RUN_TEST(should_create_with_correct_data);
    RUN_TEST(should_insert_value);
    return UNITY_END();
}
