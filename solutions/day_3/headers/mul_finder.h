#pragma once

#include <collections.h>
#include <regex.h>

ListString *find_patterns(const char *string, const char *pattern);

ListString *find_enabled_sections(const char *string);

unsigned int process_mul_instruction(ListString *instruction);

