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

    ListString *result = find_patterns(test_input, "mul\\([0-9]{1,3},[0-9]{1,3}\\)");

    TEST_ASSERT_EQUAL_STRING_ARRAY(expected_result, result->strings, 4);
}

void test_should_process_mul_instructions_correctly() {
    char *test_instruction_1 = "mul(2,4)";
    char *test_instruction_2 = "mul(8,5)";

    ListString *instructions = create_list_str(2);
    append_list_str(instructions, test_instruction_1);
    append_list_str(instructions, test_instruction_2);

    unsigned int result = process_mul_instruction(instructions);

    TEST_ASSERT_EQUAL_UINT(48, result);
}

void tearDown() {
}

int main() {
    UNITY_BEGIN();
    RUN_TEST(test_should_find_all_mul_instructions);
    RUN_TEST(test_should_process_mul_instructions_correctly);
    return UNITY_END();
}

