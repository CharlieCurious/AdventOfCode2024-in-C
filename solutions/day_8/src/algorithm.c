#include <algorithm.h>
#include <list_dict.h>

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

AntinodeTuple get_antinodes(AnthenaTuple anthenas) {
    uint distance_x = abs(anthenas.b.x - anthenas.a.x);
    uint distance_y = abs(anthenas.b.y - anthenas.b.y);

    Location c;
    c.x = anthenas.a.x - distance_x;
    c.y = anthenas.a.y - distance_y;

    Location d;
    d.x = anthenas.b.x + distance_x;
    d.y = anthenas.b.y + distance_y;

    AntinodeTuple tuple;
    tuple.a = c;
    tuple.b = d;

    return tuple;
}
