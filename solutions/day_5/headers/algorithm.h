#pragma once

#include <collections.h>
#include <rules.h>
#include <updates.h>

UpdateList *filter_updates(const UpdateList *updates, const rules_graph rules, bool get_ordered);

void fix_update(ListUInt *update, rules_graph rules);
