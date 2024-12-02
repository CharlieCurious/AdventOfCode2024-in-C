#include <banalyser.h>
#include <unity.h>

void setUp() {
}

void should_get_correct_report_size() {
    char report_1[] = "67 74 76 78 79 80 77";
    char report_2[] = "58 63 65 67 68 70 71 71";
    char report_3[] = "46 43 41 40 38 35 29 23\n";

    unsigned int result_1 = get_report_size(report_1);
    unsigned int result_2 = get_report_size(report_2);
    unsigned int result_3 = get_report_size(report_3);

    TEST_ASSERT_EQUAL_UINT(7, result_1);
    TEST_ASSERT_EQUAL_UINT(8, result_2);
    TEST_ASSERT_EQUAL_UINT(8, result_3);
}

void should_parse_report() {
    char report_1[] = "67 74 76 78 79 80 77";
    char report_2[] = "58 63 65 67 68 70 71 71";
    char report_3[] = "46 43 41 40 38 35 29 23\n";

    unsigned int expected_report_1[7] = { 67, 74, 76, 78, 79, 80, 77 };
    unsigned int expected_report_2[8] = { 58, 63, 65, 67, 68, 70, 71, 71 };
    unsigned int expected_report_3[8] = { 46, 43, 41, 40, 38, 35, 29, 23 };


    unsigned int *result_1 = parse_report(report_1, 7);
    unsigned int *result_2 = parse_report(report_2, 8);
    unsigned int *result_3 = parse_report(report_3, 8);

    TEST_ASSERT_EQUAL_UINT_ARRAY(expected_report_1, result_1, 7);
    TEST_ASSERT_EQUAL_UINT_ARRAY(expected_report_2, result_2, 8);
    TEST_ASSERT_EQUAL_UINT_ARRAY(expected_report_3, result_3, 8);
}

void should_determine_safe_report_decreasing() {
    unsigned int report[5] = { 7, 6, 4, 2, 1 }; 

    bool result = is_report_safe(report, 5);

    TEST_ASSERT_TRUE(result);
}

void should_determine_safe_report_increasing() {
    unsigned int report[5] = { 1, 3, 6, 7, 9 }; 

    bool result = is_report_safe(report, 5);

    TEST_ASSERT_TRUE(result);
}

void should_determine_unsafe_report_if_order_changes_to_decreasing() {
    unsigned int report[5] = { 1, 3, 2, 4, 5 }; 

    bool result = is_report_safe(report, 5);

    TEST_ASSERT_FALSE(result);
}

void should_determine_unsafe_report_if_order_changes_to_increasing() {
    unsigned int report[5] = { 5, 4, 6, 2, 1 }; 

    bool result = is_report_safe(report, 5);

    TEST_ASSERT_FALSE(result);
}

void should_determine_unsafe_report_if_difference_too_big() {
    unsigned int report[5] = { 9, 7, 6, 2, 1 }; 

    bool result = is_report_safe(report, 5);

    TEST_ASSERT_FALSE(result);
}

void should_determine_unsafe_report_if_difference_too_small() {
    unsigned int report[5] = { 8, 6, 4, 4, 1 }; 

    bool result = is_report_safe(report, 5);

    TEST_ASSERT_FALSE(result);
}

// ------------------------------------------- Part 2 tests ------------------------------------------------


void tearDown() {
}

int main() {
    UNITY_BEGIN();
    RUN_TEST(should_get_correct_report_size);
    RUN_TEST(should_parse_report);
    RUN_TEST(should_determine_safe_report_decreasing);
    RUN_TEST(should_determine_safe_report_increasing);
    RUN_TEST(should_determine_unsafe_report_if_order_changes_to_decreasing);
    RUN_TEST(should_determine_unsafe_report_if_order_changes_to_increasing);
    RUN_TEST(should_determine_unsafe_report_if_difference_too_big);
    RUN_TEST(should_determine_unsafe_report_if_difference_too_small);

    // part 2

    return UNITY_END();
}

