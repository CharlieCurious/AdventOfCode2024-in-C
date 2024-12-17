#pragma once

#include <list_dict.h>
 
typedef struct AnthenaTuple {
    Location a;
    Location b;
} AnthenaTuple;

typedef struct AntinodeTuple {
    Location a;
    Location b;
} AntinodeTuple;

AnthenaTuple *get_anthena_tuples(LocationList *location_list, uint *out_num_tuples);
AntinodeTuple get_antinodes(AnthenaTuple anthenas);
