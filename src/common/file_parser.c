#include <file_parser.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILE_SIZE 1048576 // 1 MB
#define MAX_NUMBER_OF_LINES 1024
#define MAX_LINE_LENGHT 256

FILE *open_input_file(const char *file_path) {
    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        fprintf(stderr, "Could not open file: %s\n", file_path);
        return NULL;
    }
    return file;
}

void read_input_lines(FILE *input_file, InputLines *input_lines) {
    char **lines = (char **)malloc(MAX_NUMBER_OF_LINES * sizeof(char *));
    if (lines == NULL) {
        perror("Failed to allocate memory for lines");
        return;
    }

    char line_buffer[MAX_LINE_LENGHT];

    size_t line_count = 0;
    while (fgets(line_buffer, sizeof(line_buffer), input_file) != NULL 
            && line_count < MAX_NUMBER_OF_LINES) {
        lines[line_count] = strdup(line_buffer);
        
        if (lines[line_count] == NULL) {
            fprintf(stderr, "Failed to allocate memory for line: %s\n", line_buffer);
        }

        line_count++;
    }

    input_lines->lines = lines;
    input_lines->count = line_count;
}

void free_input_lines(InputLines *input_lines) {
    if (input_lines == NULL)
        return;

    for (size_t i = 0; i < input_lines->count; i++) {
        free(input_lines->lines[i]);
        input_lines->lines[i] = NULL;
    }

    free(input_lines->lines);
    input_lines->lines = NULL;

    free(input_lines);
    input_lines = NULL;
}














