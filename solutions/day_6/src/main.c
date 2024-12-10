#include <file_parser.h>
#include <path_finder.h>
#include <path_tracer.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#define GUARD_X 6
#define GUARD_Y 4
#define MAX_FILE_LINES 1000
#define MAX_LINE_LEN 1000

Grid *grid_create(FILE *file) {
    char **lines = (char **)calloc(MAX_FILE_LINES, sizeof(char *));

    char buffer[MAX_LINE_LEN];
    size_t line_count = 0;
    size_t guard_x, guard_y;
    const char guard_symbol = GUARD;
    while (fgets(buffer, sizeof(buffer), file) && line_count < MAX_FILE_LINES) {
        buffer[strlen(buffer) - 1] = '\0';
        lines[line_count] = strdup(buffer);

        char *guard_pos = strchr(buffer, guard_symbol);
        if (guard_pos) {
            guard_x = line_count;
            guard_y = guard_pos - buffer;
        }

        line_count++;
    }

    Grid *grid = (Grid *)malloc(sizeof(Grid));
    grid->width = 10;
    grid->height = 10;
    grid->map = lines;

    rewind(file);
    return grid;
}

int main() {
    FILE *file = fopen("input_files/day_6.txt", "r");
    if (!file) {
        perror("Could not open input file");
        return EXIT_FAILURE;
    }

    Grid *grid_part_1 = grid_create(file);
    HashSet *path_tracer;

    path_tracer = hashset_create(grid_part_1->height * grid_part_1->width);
    Step first_step = step_create(GUARD_X, GUARD_Y, NORTH);
    int part_1 = follow_col_north(grid_part_1, first_step, 0, path_tracer);
    hashset_free(path_tracer);
    path_tracer = NULL;


    int part_2 = 0;
    for (size_t x = 0; x < grid_part_1->height; x++) {
        for (size_t y = 0; y < grid_part_1->width; y++) {
            // create new grid
            Grid *grid_part_2 = grid_create(file);
            grid_part_2->map[x][y] = PRINTER;

            first_step = step_create(GUARD_X, GUARD_Y, NORTH);
            HashSet *path_tracer = hashset_create(grid_part_2->height * grid_part_2->width);

            if (follow_col_north(grid_part_2, first_step, 0, path_tracer) == -1) {
                part_2++;
                puts("found loop");
                print_grid(grid_part_2, x);
            }

            // free
            //hashset_free(path_tracer);
            path_tracer = NULL;
            //free(grid_part_2);
            grid_part_2 = NULL;
        }
    }

    fclose(file);
    printf("Part 1: %d\nPart 2: %d\n", part_1, part_2);

    return EXIT_SUCCESS;
}

