#include <permutations.h>
#include <unity.h>
#include <stdlib.h>
#include <sys/types.h>

void setUp() {
}

void should_calculate_permutations() {
    uint numbers_count = 2;
    uint total_permutations = 1 << numbers_count;
    char **permutations = (char **)malloc(total_permutations * sizeof(char *));
    char *slots = (char *)malloc(numbers_count * sizeof(char));
    size_t count = 0;

    char *expected_result[4] = { "++", "+*", "*+", "**" };

    permutations_generate(permutations, &count, slots, numbers_count, 0);

    TEST_ASSERT_EQUAL_size_t_MESSAGE(4, count, "Test right number of permutations");
    TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected_result, permutations, 4, "Test right permutations");
}

void tearDown() {
}

int main() {
    UNITY_BEGIN();
    RUN_TEST(should_calculate_permutations);
    return UNITY_END();
}
