#pragma once

#include <collections.h>
#include <regex.h>

ListString *find_instructions(const char *string, const char *pattern);

char *remove_substring(const char *string);

unsigned int process_mul_instruction(ListString *instruction);

