#include "unity_internals.h"
#include <algorithm.h>
#include <unity.h>
#include <updates.h>
#include <rules.h>

char test_rules[] =          "47|53\n"
                            "97|13\n"
                            "97|61\n"
                            "97|47\n"
                            "75|29\n"
                            "61|13\n"
                            "75|53\n"
                            "29|13\n"
                            "97|29\n"
                            "53|29\n"
                            "61|53\n"
                            "97|53\n"
                            "61|29\n"
                            "47|13\n"
                            "75|47\n"
                            "97|75\n"
                            "47|61\n"
                            "75|61\n"
                            "47|29\n"
                            "75|13\n"
                            "53|13";

char test_updates[] =  "75,47,61,53,29\n"
                            "97,61,53,29,13\n"
                            "75,29,13\n"
                            "75,97,47,61,53\n"
                            "61,13,29\n"
                            "97,13,75,29,47";

void setUp() {
}

void should_get_ordered_updates() {
    rules_graph rules = init_rules_graph(test_rules, 99);
    UpdateList *updates = parse_updates_str(test_updates, 6); 

    uint result0[5] = { 75, 47, 61, 53, 29 };
    uint result1[5] = { 97, 61, 53, 29, 13 };
    uint result2[3] = { 75, 29, 13 };

    UpdateList *result = filter_ordered_updates(updates, rules);

    TEST_ASSERT_EQUAL_UINT_ARRAY_MESSAGE(result0, result->updates[0]->uints, 5, "Assert result[0]");
    TEST_ASSERT_EQUAL_UINT_ARRAY_MESSAGE(result1, result->updates[1]->uints, 5, "Assert result[1]");
    TEST_ASSERT_EQUAL_UINT_ARRAY_MESSAGE(result2, result->updates[2]->uints, 3, "Assert result[2]");
}


void tearDown() {
}

int main() {
    UNITY_BEGIN();
    RUN_TEST(should_get_ordered_updates);
    return UNITY_END();
}
