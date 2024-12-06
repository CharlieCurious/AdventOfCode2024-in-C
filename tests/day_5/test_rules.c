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

   rules_graph result = init_rules_graph(rules, 10);

   for (unsigned int x = 0; x < 11; x++) {
       for (unsigned int y = 0; y < 11; y++) {
          bool should_be_true = ((x == 6 && y == 2) || 
              (x == 10 && y == 5) ||
              (x == 3 && y == 8));

          bool is_in_rules = result[x][y];
          if (should_be_true) {
              TEST_ASSERT(is_in_rules);
          } else {
              TEST_ASSERT(!is_in_rules);
          }
       }
   }
}

void tearDown() {
}


int main() {
    UNITY_BEGIN();
    RUN_TEST(should_return_null_if_invalid_rule);
    RUN_TEST(should_init_graph);
    return UNITY_END();
}
