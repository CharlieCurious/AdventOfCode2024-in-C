#pragma once

#include <collections.h>
#include <regex.h>

ListString *find_patterns(const char *string, const char *pattern);

unsigned int process_mul_instruction(ListString *instruction);
