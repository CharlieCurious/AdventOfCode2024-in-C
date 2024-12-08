#pragma once

#include <stdbool.h>

typedef bool** rules_graph;

rules_graph init_rules_graph(char *rules_str, unsigned int num_rules);
