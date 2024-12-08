#include <algorithm.h>
#include <collections.h>
#include <rules.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <updates.h>

static bool is_update_in_order(const ListUInt *single_update, const rules_graph rules); 

UpdateList *filter_updates(const UpdateList *updates, const rules_graph rules, bool get_ordered) {
    ListUInt *ordered_updates_buffer[updates->num_updates];
    
    size_t count = 0;
    for (size_t i = 0; i < updates->num_updates; i++) {
        ListUInt *update = updates->updates[i];
        bool is_ordered = is_update_in_order(update, rules);
        if (is_ordered == get_ordered)
            ordered_updates_buffer[count++] = update;
    }

    UpdateList *filtered = (UpdateList *)malloc(sizeof(UpdateList));

    ListUInt **ordered_updates = (ListUInt **)malloc(count * sizeof(ListUInt *));

    memcpy(ordered_updates, ordered_updates_buffer, count * sizeof(ListUInt *));

    filtered->updates = ordered_updates;
    filtered->num_updates = count;

    return filtered;
}

static bool is_update_in_order(const ListUInt *single_update, const rules_graph rules) {

    bool error_detected = false;
    for (size_t i = 0; i < single_update->size - 1; i++) {
        for (size_t j = i + 1; j < single_update->size; j++) {
            if (rules[single_update->uints[j]][single_update->uints[i]])
                return false;
        }
    }
    return true;
}
