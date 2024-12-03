#include <collections.h>
#include <mul_finder.h>
#include <unity.h>

void setUp() {
}

void test_should_find_all_mul_instructions() {
    const char test_input[84] = "xmul(2,4)%&mul[3,7]!@^do_not_mul(5,5)+mul(32,64]then(mul(11,8)mul(8,5))mul ( 2 , 4 )";
    const char *expected_result[] = {
        "mul(2,4)",
        "mul(5,5)",
        "mul(11,8)",
        "mul(8,5)"
    };

    ListString *result = find_mul_instructions(test_input, 84);

    TEST_ASSERT_EQUAL_STRING_ARRAY(expected_result, result->strings, 4);
}

void test_should_process_mul_instructions_correctly() {
    const char *test_instruction_1 = "mul(2,4)";
    const char *test_instruction_2 = "mul(8,5)";

    unsigned int result_1 = process_mul_instruction(test_instruction_1);
    unsigned int result_2 = process_mul_instruction(test_instruction_2);

    TEST_ASSERT_EQUAL_UINT(8, result_1);
    TEST_ASSERT_EQUAL_UINT(40, result_2);
}

void tearDown() {
}

int main() {
    UNITY_BEGIN();
    RUN_TEST(test_should_find_all_mul_instructions);
    RUN_TEST(test_should_process_mul_instructions_correctly);
    return UNITY_END();
}

