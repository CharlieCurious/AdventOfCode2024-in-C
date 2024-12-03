#pragma once

#include <collections.h>
#include <regex.h>

ListString *find_mul_instructions(const char *string, const unsigned int program_length);

unsigned int process_mul_instruction(const char *instruction);
