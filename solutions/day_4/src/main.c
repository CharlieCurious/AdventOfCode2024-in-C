#include <file_parser.h>
#include <matrix_search.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static unsigned int xmas_in_winds(char **winds, unsigned int line, unsigned int col);

int main() {
    FILE *file = open_input_file("input_files/day_4.txt");
    if (!file) exit(EXIT_FAILURE);

    InputLines *lines = read_input_lines(file);
    fclose(file);
    if(!lines) exit(EXIT_FAILURE);

    unsigned int part_1 = 0;
    for (size_t i = 0; i < lines->count; i++) {
        char *line = lines->lines[i];

        for (size_t j = 0; line[j] != '\0'; j++) {
            if (line[j] == 'X') {
                char **winds = get_compass_rose(lines, i, j);
                part_1 += xmas_in_winds(winds, i, j);
            }
        }
    }

    printf("Part 1: %u\n", part_1); 

    free_input_lines(&lines);
}

static unsigned int xmas_in_winds(char **winds, unsigned int line, unsigned int col) {
    unsigned int xmas_count = 0;

    for (size_t i = 0; i < 8; i++) {
        if (winds[i] != NULL && strcmp("XMAS", winds[i]) == 0) 
            xmas_count ++;
    }

    printf("Found %u XMASs for x at (%u, %u)\n", xmas_count, line, col);

    return xmas_count;
}
