#pragma once

#include <list_dict.h>
 
typedef struct AnthenaTuple {
    Location a;
    Location b;
} AnthenaTuple;

AnthenaTuple *get_anthena_tuples(LocationList *location_list);
