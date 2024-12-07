#pragma once

#include <rules.h>
#include <updates.h>

UpdateList *filter_ordered_updates(const UpdateList *updates, const rules_graph rules);
