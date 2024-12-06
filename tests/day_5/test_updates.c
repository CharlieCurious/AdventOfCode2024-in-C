#include <unity.h>
#include <updates.h>

void setUp() {
}

void should_return_update_lines() {
    const char *test_updates =  "48,54,34,53\n"
                                "23,78,2\n"
                                "23,34,23,45,23\n";

    unsigned int row0[] = { 48, 54, 34, 53 };
    unsigned int row1[] = { 23, 78, 2 };
    unsigned int row2[] = { 23, 34, 23, 45, 23 };

    unsigned int *expected_result[] = { row0, row1, row2 };

    unsigned int **result = parse_updates_str(test_updates, 3);

    TEST_ASSERT_EQUAL_UINT_ARRAY_MESSAGE(expected_result[0], result[0], 4, "Assert row 0");
    TEST_ASSERT_EQUAL_UINT_ARRAY_MESSAGE(expected_result[1], result[1], 3, "Assert row 1");
    TEST_ASSERT_EQUAL_UINT_ARRAY_MESSAGE(expected_result[2], result[2], 5, "Assert row 2");
}

void tearDown() {
}

int main() {
    UNITY_BEGIN();
    RUN_TEST(should_return_update_lines);
    return UNITY_END();
}
