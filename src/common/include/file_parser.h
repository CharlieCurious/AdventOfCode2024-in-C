#include <stdio.h>

typedef struct {
    char **lines;
    size_t count;
} InputLines;

// If input file cannot be opened, nothing will work -- se we exit the program.
FILE *open_file_or_exit(const char *file_path);

void read_input_lines(FILE *input_file, InputLines *input_lines);

void free_input_lines(InputLines *input_lines);
