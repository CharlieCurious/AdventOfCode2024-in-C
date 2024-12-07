#include <algorithm.h>
#include <collections.h>
#include <rules.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <updates.h>

static bool is_update_in_order(const ListUInt *single_update, const rules_graph rules); 

UpdateList *filter_ordered_updates(const UpdateList *updates, const rules_graph rules) {
    ListUInt *ordered_updates_buffer[updates->num_updates];
    
    size_t count = 0;
    for (size_t i = 0; i < updates->num_updates; i++) {
        ListUInt *update = updates->updates[i];
        if (is_update_in_order(update, rules))
            ordered_updates_buffer[count++] = update;
    }

    UpdateList *filtered = (UpdateList *)malloc(sizeof(UpdateList));
    if (!filtered) {
        perror("Failed to allocate for filtered updates");
        return NULL;
    }

    ListUInt **ordered_updates = (ListUInt **)malloc(count * sizeof(ListUInt *));
    if (!ordered_updates) {
        perror("Failed to allocate for filtered updates");
        free(filtered);
        return NULL;
    }

    memcpy(ordered_updates, ordered_updates_buffer, count * sizeof(ListUInt *));

    filtered->updates = ordered_updates;
    filtered->num_updates = count;

    return filtered;
}

static bool is_update_in_order(const ListUInt *single_update, const rules_graph rules) {

    bool error_detected = false;
    for (size_t i = 0; i < single_update->size - 1; i++) {
        if (contains_rule(rules, single_update->uints[i+1], single_update->uints[i]))
                return false;
    }
    return true;
}
