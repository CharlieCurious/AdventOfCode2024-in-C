#include <list_dict.h>
#include <unity.h>

#define TEST_DICT_CAPACITY 10

AnthenasDictionary *dict;

void setUp() {
    dict = dictionary_create(TEST_DICT_CAPACITY);
}

void should_create_dict_correctly() {
    TEST_ASSERT_EQUAL_size_t_MESSAGE(TEST_DICT_CAPACITY, dict->capacity, "Test right initial capacity");
    TEST_ASSERT_NULL(dict->kvp[0]);
}

void should_insert_value_in_dict() {
    char key = 'A';
    Location location;
    location.x = 2;
    location.y = 3;
    size_t index = (key * 31) % TEST_DICT_CAPACITY;

    bool insert_result = dictionary_insert(dict, key, location);
    KeyValue *inserted_kv = dict->kvp[index];
    LocationList *inserted_loc_list = inserted_kv->value;

    TEST_ASSERT_TRUE_MESSAGE(insert_result, "Test insert returns true");
    TEST_ASSERT_EQUAL_MESSAGE(inserted_kv->key, key, "Test inserted key correct");
    TEST_ASSERT_NULL_MESSAGE(inserted_kv->next, "Test next kv is null");

    TEST_ASSERT_NOT_NULL(inserted_loc_list);
    TEST_ASSERT_NOT_NULL(inserted_loc_list->locations);
    TEST_ASSERT_EQUAL_size_t_MESSAGE(1, inserted_loc_list->size, "Test inserted list size");
    TEST_ASSERT_EQUAL_size_t_MESSAGE(INITIAL_MAX_LOCATIONS_PER_SYMBOL, inserted_loc_list->capacity, "Test inserted list capacity");
    TEST_ASSERT_TRUE_MESSAGE(location_equal(location, inserted_loc_list->locations[0]), "Test inserted location is correct");
}

void should_get_value_in_dict() {
    char key = 'A';
    Location location;
    location.x = 2;
    location.y = 3;
    dictionary_insert(dict, key, location);

    LocationList *result = dictionary_get(dict, key);

    TEST_ASSERT_NOT_NULL_MESSAGE(result, "Test get result is not null");
    TEST_ASSERT_TRUE_MESSAGE(location_equal(result->locations[0], location), "Test got location is right");
}

void tearDown() {
    if (!dict)
        return;
    dictionary_free(dict); 
    dict = NULL;
}

int main() {
    UNITY_BEGIN();
    RUN_TEST(should_create_dict_correctly);
    RUN_TEST(should_insert_value_in_dict);
    RUN_TEST(should_get_value_in_dict);
    return UNITY_END();
}
