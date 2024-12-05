#pragma once

#include <stdio.h>

typedef struct {
    char **lines;
    size_t count;
} InputLines;

// If input file cannot be opened, nothing will work -- se we exit the program.
FILE *open_input_file(const char *file_path);

InputLines *read_input_lines(FILE *input_file);

InputLines *read_input_lines_from_str(const char *input_str);

void free_input_lines(InputLines **input_lines);
