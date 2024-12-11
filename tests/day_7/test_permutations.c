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

    free(permutations);
    free(slots);
}

void should_return_true_if_equation_possible() {
    char *permutation[1] = { "*++" };
    int numbers[4] = { 2, 2, 3, 7 };
    Equation equation;
    equation.numbers = numbers;
    equation.result = 14;
    equation.numbers_count = 4;

    bool result = has_possible_equation(&equation, permutation, 1);

    TEST_ASSERT_TRUE_MESSAGE(result, "Test valid equation");
}

void should_return_false_if_equation_not_possible() {
    char *permutation[1] = { "*++" };
    int numbers[4] = { 2, 2, 3, 7 };
    Equation equation;
    equation.numbers = numbers;
    equation.result = 15;
    equation.numbers_count = 4;

    bool result = has_possible_equation(&equation, permutation, 1);

    TEST_ASSERT_FALSE_MESSAGE(result, "Test invalid equation");
}

void tearDown() {
}

int main() {
    UNITY_BEGIN();
    RUN_TEST(should_calculate_permutations);
    RUN_TEST(should_return_true_if_equation_possible);
    RUN_TEST(should_return_false_if_equation_not_possible);
    return UNITY_END();
}
