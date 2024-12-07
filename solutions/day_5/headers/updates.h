#pragma once

#include <collections.h>
#include <stdlib.h>



typedef struct UpdateList {
    ListUInt **updates;
    size_t num_updates;
} UpdateList;

UpdateList *parse_updates_str(const char *updates, uint num_updates);

void free_update_list(UpdateList **update_list);
