#pragma once

#include <rules.h>
#include <updates.h>

UpdateList *filter_updates(const UpdateList *updates, const rules_graph rules, bool get_ordered);
