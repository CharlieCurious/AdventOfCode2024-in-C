#include <path_tracer.h>
#include <unity.h>

HashSet *set = NULL;

void setUp() {
}

void should_create_hashset_with_correct_parameters() {
    set = hashset_create(10);

    TEST_ASSERT_EQUAL_size_t_MESSAGE(10, set->capacity, "Initial capacity");
    TEST_ASSERT_EQUAL_size_t_MESSAGE(0, set->size, "Initial size");
    TEST_ASSERT_EQUAL_size_t_MESSAGE(10 * sizeof(Node *),  10 * sizeof(set->nodes), "Node memory size");

}

void should_return_true_on_insert() {
    set = hashset_create(10);
    Step step = step_create(1, 3, NORTH);

    bool result = hashset_insert(set, step);

    TEST_ASSERT_TRUE_MESSAGE(result, "Test insert returns true");
}

void should_return_false_if_element_is_contained() {
    set = hashset_create(10);
    Step step = step_create(1, 3, NORTH);
    hashset_insert(set, step);

    bool result = hashset_insert(set, step);

    TEST_ASSERT_FALSE_MESSAGE(result, "Test insert returns true");
}

void should_resize_if_full() {
    set = hashset_create(1);
    Step step_0 = step_create(1, 3, NORTH);
    hashset_insert(set, step_0);
    size_t previous_capacity = set->capacity;

    Step step_1 = step_create(1, 4, NORTH);
    bool result = hashset_insert(set, step_1);
    
    TEST_ASSERT_TRUE_MESSAGE(result, "Test insert returns true after resize");
    TEST_ASSERT_EQUAL_size_t_MESSAGE(previous_capacity * 2, set->capacity, "Test insert resize to *2");
}

void tearDown() {
    if (!set)
        return;
    hashset_free(set);
    set = NULL;
}

int main() {
    UNITY_BEGIN();
    RUN_TEST(should_create_hashset_with_correct_parameters);
    RUN_TEST(should_return_true_on_insert);
    RUN_TEST(should_return_false_if_element_is_contained);
    RUN_TEST(should_resize_if_full);
    return UNITY_END();
}
