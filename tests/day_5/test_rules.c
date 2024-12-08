#include <rules.h>
#include <unity.h>
#include <stdbool.h>

void setUp() {
}

void should_return_null_if_invalid_rule() {
    char invalid_rule[4] = "$|^\n";

    rules_graph result = init_rules_graph(invalid_rule, 1);

    TEST_ASSERT_NULL(result);
}

void should_init_graph() {
    char rules[] =   "6|2\n"
        "10|5\n"
        "3|8";

    rules_graph result = init_rules_graph(rules, 99);

    TEST_ASSERT_FALSE(result[1][1]);

    TEST_ASSERT_TRUE(result[6][2]);
    TEST_ASSERT_TRUE(result[10][5]);
    TEST_ASSERT_TRUE(result[3][8]);
}

void tearDown() {
}


int main() {
    UNITY_BEGIN();
    RUN_TEST(should_return_null_if_invalid_rule);
    RUN_TEST(should_init_graph);
    return UNITY_END();
}
