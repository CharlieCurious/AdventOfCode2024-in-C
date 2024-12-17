#pragma once

#include <list_dict.h>
 
typedef struct AnthenaTuple {
    Location a;
    Location b;
} AnthenaTuple;

AnthenaTuple *get_anthena_tuples(LocationList *location_list, uint *out_num_tuples);

void add_anthena_tuple_antinodes(AnthenaTuple tuple);



