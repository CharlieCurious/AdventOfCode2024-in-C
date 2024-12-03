#include <collections.h>
#include <unity.h>

void setUp() {
}

void test_should_create_list_with_correct_size() {
    ListString *list = create_list_str(10);

    TEST_ASSERT_EQUAL_size_t_MESSAGE(0, list->size, "Assert size");
    TEST_ASSERT_EQUAL_size_t_MESSAGE(10, list->capacity, "Assert capacity");

}

void test_should_append_string_to_list() {
    ListString *list = create_list_str(1);
    size_t initial_size = list->size;
    char *expected_strings[1] = { "test_string" };

    append_list_str(list, "test_string");

    TEST_ASSERT_EQUAL_size_t_MESSAGE(initial_size + 1, list->size, "Assert size is correct");
    TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(
            expected_strings, 
            list->strings, 
            1, 
            "Assert string equal str array");
}

void test_should_free_list() {
    ListString *list = create_list_str(1);

    free_list_str(&list);

    TEST_ASSERT_NULL(list);
}

void tearDown() {
}

int main() {
    UNITY_BEGIN();
    RUN_TEST(test_should_create_list_with_correct_size);
    RUN_TEST(test_should_append_string_to_list);
    RUN_TEST(test_should_free_list);
    return UNITY_END();
}



