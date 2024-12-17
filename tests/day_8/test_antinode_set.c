#include <list_dict.h>
#include <unity.h>

#define INITIAL_CAPACITY 10

AntinodeSet *set;

void setUp() {
    set = antinode_set_create(INITIAL_CAPACITY);
}

void should_create_set_with_corrent_parameters() {
    TEST_ASSERT_EQUAL_size_t_MESSAGE(10, set->capacity, "Test correct initial capacity");
    TEST_ASSERT_EQUAL_size_t_MESSAGE(0, set->size, "Test correct initial size");
    
    // Assert all nodes are set to null
    for (size_t i = 0; i < set->capacity; i++) {
        TEST_ASSERT_NULL_MESSAGE(set->nodes[i], "Test node is NULL");
    }
}

void should_return_true_when_insert() {
    Location a;
    a.x = 1;
    a.y = 1;

    bool result = antinode_set_insert(set, a);
    size_t index = antinode_hash(a) % set->capacity;
    Location inserted = set->nodes[index]->value;

    TEST_ASSERT_EQUAL_size_t_MESSAGE(1, set->size, "Test size updated");
    TEST_ASSERT_TRUE_MESSAGE(result, "Test insert result is true");
    TEST_ASSERT_TRUE_MESSAGE(location_equal(inserted, a), "Test inserted value is correct");
}

void should_increase_capacity_if_full() {
    antinode_set_free(set);
    set = antinode_set_create(0); // intial capacity to 0
    
    Location a;
    a.x = 1;
    a.y = 1;

    bool result = antinode_set_insert(set, a);
    Location inserted = set->nodes[0]->value;

    TEST_ASSERT_EQUAL_size_t_MESSAGE(1, set->capacity, "Test new capacity is correct");
    TEST_ASSERT_TRUE_MESSAGE(result, "Test insert result is true");
    TEST_ASSERT_TRUE_MESSAGE(location_equal(inserted, a), "Test inserted value is correct");
}

void tearDown() {
    if (!set)
        return;
    antinode_set_free(set);
    set = NULL;
}

int main() {
    UNITY_BEGIN();
    RUN_TEST(should_create_set_with_corrent_parameters);
    RUN_TEST(should_return_true_when_insert);
    RUN_TEST(should_increase_capacity_if_full);
    return UNITY_END();
}
