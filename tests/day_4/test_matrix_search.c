#include <file_parser.h>
#include <matrix_search.h>
#include <unity.h>

void setUp() {
}

void should_get_compass_rose() {
    char *test_string = "R__C__O\n"
                        "_Q_B_N_\n"
                        "__PAM__\n"
                        "LKJXDEF\n"
                        "__VGS__\n"
                        "_Y_H_T_\n"
                        "Z__I__U\n";

    char *expected_strings[8] = {
        "XABC",
        "XMNO",
        "XDEF",
        "XSTU",
        "XGHI",
        "XVYZ",
        "XJKL",
        "XPQR"
    };

    InputLines *lines = read_input_lines_from_str(test_string);

    char **result = get_compass_rose(lines, 3, 3);

    TEST_ASSERT_EQUAL_STRING_ARRAY(expected_strings, result, 8);

    free_input_lines(&lines);
}

void tearDown() {
}

int main() {
    UNITY_BEGIN();
    RUN_TEST(should_get_compass_rose);
    return UNITY_END();
}
