#include <file_parser.h>
#include <matrix_search.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static unsigned int xmas_in_winds(char **winds, unsigned int line, unsigned int col);
static bool is_xmas_square(char **lines, size_t a_index, size_t line_index);

// -----------------------------------
// The real good way to solve this would be to use a trie like approach for part 1
// so it would check the winds and assess at the same time, while saving array memory.
// Also use 2 pointers to iterate from 2 directions.
// ------------------------------------------------
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

    unsigned int part_2 = 0;
    size_t line_len = strlen(lines->lines[0]);

    for (size_t i = 1; i < lines->count - 1; i++) {
        char *line = lines->lines[i];

        for (size_t j = 1; j < line_len - 2; j++) {
            if (line[j] == 'A' && is_xmas_square(lines->lines, j, i))
               part_2++; 
        }
    }

    printf("Part 1: %u\nPart 2: %u\n", part_1, part_2); 

    free_input_lines(&lines);
}

static unsigned int xmas_in_winds(char **winds, unsigned int line, unsigned int col) {
    unsigned int xmas_count = 0;

    for (size_t i = 0; i < 8; i++) {
        if (winds[i] != NULL && strcmp("XMAS", winds[i]) == 0) 
            xmas_count ++;
    }

    return xmas_count;
}

static bool is_xmas_square(char **lines, size_t a_index, size_t line_index) {

    char north_west = lines[line_index-1][a_index-1];
    char south_east = lines[line_index+1][a_index+1];

    bool makes_backslash = (north_west == 'M' && south_east == 'S') ||
        (north_west == 'S' && south_east == 'M');

    if (makes_backslash) {
        char north_east = lines[line_index-1][a_index+1];
        char south_west = lines[line_index+1][a_index-1];

        return (north_east == 'M' && south_west == 'S') ||
            (north_east == 'S' && south_west == 'M');
    }

    return false;
    
}
