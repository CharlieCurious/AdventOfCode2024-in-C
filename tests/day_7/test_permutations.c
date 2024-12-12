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
    long numbers[4] = { 2, 2, 3, 7 };
    Equation equation;
    equation.numbers = numbers;
    equation.result = 14;
    equation.numbers_count = 4;

    bool result = has_possible_equation(&equation, permutation, 1);

    TEST_ASSERT_TRUE_MESSAGE(result, "Test valid equation");
}

void should_return_false_if_equation_not_possible() {
    char *permutation[1] = { "*++" };
    long numbers[4] = { 2, 2, 3, 7 };
    Equation equation;
    equation.numbers = numbers;
    equation.result = 15;
    equation.numbers_count = 4;

    bool result = has_possible_equation(&equation, permutation, 1);

    TEST_ASSERT_FALSE_MESSAGE(result, "Test invalid equation");
}

void should_generate_permutations_for_equation() {
    long numbers[3] = { 1, 2, 3 };
    Equation equation;
    equation.numbers = numbers;
    equation.numbers_count = 3;

    char *expected_result[4] = { "++", "+*", "*+", "**" };

    size_t num_permutations;
    char **result = get_permutations_for_equation(&equation, &num_permutations);

    TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected_result, result, 4, "Test generate permutations for equation");
    TEST_ASSERT_EQUAL_size_t_MESSAGE(4, num_permutations, "Test correct num of permutations for equation");

    for (size_t i = 0; i < 4; i++) {
        if (result[i])
            free(result[i]);
    }
    free(result);
}

void should_calculate_sum_of_valid_equations() {
    Equation equation_0;
    long equation_0_nums[2] = { 10, 19 };
    equation_0.numbers_count = 2;
    equation_0.result = 190;

    Equation equation_1;
    long equation_1_nums[3] = { 81, 40, 27 };
    equation_1.numbers_count = 3;
    equation_1.result = 3267;

    Equation equation_2;
    long equation_2_nums[2] = { 17, 5 };
    equation_2.numbers_count = 2;
    equation_2.result = 83;

    Equation equation_3;
    long equation_3_nums[4] = { 11, 6, 16, 20 };
    equation_3.numbers_count = 4;
    equation_3.result = 292;

    Equation *equations[4] = { &equation_0, &equation_1, &equation_2, &equation_3 };

    long long result = get_possible_permutations_sum(equations, 4);

    TEST_ASSERT_EQUAL_INT64_MESSAGE(3749, result, "Test sum of valid equations");
}

void tearDown() {
}

int main() {
    UNITY_BEGIN();
    RUN_TEST(should_calculate_permutations);
    RUN_TEST(should_return_true_if_equation_possible);
    RUN_TEST(should_return_false_if_equation_not_possible);
    RUN_TEST(should_generate_permutations_for_equation);
    RUN_TEST(should_calculate_sum_of_valid_equations);
    return UNITY_END();
}
