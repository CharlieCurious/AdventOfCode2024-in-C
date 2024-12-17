#include <algorithm.h>

AnthenaTuple *get_anthena_tuples(LocationList *location_list, uint *out_num_tuples) {
    size_t location_list_size = location_list->size;
    uint num_tuples = (location_list_size * (location_list_size - 1)) / 2; 

    AnthenaTuple *tuples = (AnthenaTuple *)malloc(num_tuples * sizeof(AnthenaTuple));
    if (!tuples)
        return NULL;

    size_t index = 0;
    AnthenaTuple tuple;
    for (size_t i = 0; i < location_list_size - 1; i++) {
        for (size_t j = i + 1; j < location_list_size; j++) {
            tuple.a = location_list->locations[i];
            tuple.b = location_list->locations[j];
            tuples[index++] = tuple;
        }
    }

    *out_num_tuples = num_tuples;
    return tuples;
}
