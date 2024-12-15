#include <algorithm.h>
#include <list_dict.h>
#include <unity.h>
#include <stdbool.h>

static bool tuples_equal(AnthenaTuple this, AnthenaTuple that);

void setUp() {
}

void should_get_anthena_tuples() {
    Location a;
    a.x = 0;
    a.y = 2;
    Location b;
    b.x = 1;
    b.y = 2;
    Location c;
    c.x = 3;
    c.y = 3;

    Location values[3] = { a, b, c };

    LocationList list;
    list.size = 3;
    list.capacity = 3;
    list.locations = values;

    AnthenaTuple tuple_0;
    tuple_0.a = a;
    tuple_0.b = b;

    AnthenaTuple tuple_1;
    tuple_1.a = a;
    tuple_1.b = c;

    AnthenaTuple tuple_2;
    tuple_2.a = b;
    tuple_2.b = c;

    AnthenaTuple *result = get_anthena_tuples(&list);

    TEST_ASSERT_TRUE_MESSAGE(tuples_equal(result[0], tuple_0), "Test 1st tuple currect");
    TEST_ASSERT_TRUE_MESSAGE(tuples_equal(result[1], tuple_1), "Test 2nd tuple currect");
    TEST_ASSERT_TRUE_MESSAGE(tuples_equal(result[2], tuple_2), "Test 3rd tuple currect");
}

static bool tuples_equal(AnthenaTuple this, AnthenaTuple that) {
    return location_equal(this.a, that.a) && location_equal(this.b, that.b);
}

void tearDown() {
}

int main() {
    UNITY_BEGIN();
    return UNITY_END();
}
