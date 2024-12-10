#include <path_finder.h>
#include <path_tracer.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#define MAX_FILE_LINES 1000
#define MAX_LINE_LEN 1000

int main() {
    FILE *file = fopen("input_files/day_6.txt", "r");
    if (!file) {
        perror("Could not open input file");
        return EXIT_FAILURE;
    }

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
    grid->width = strlen(buffer);
    grid->height = line_count;
    grid->map = lines;

    HashSet *path_tracer;

    path_tracer = hashset_create(grid->height * grid->width);
    Step first_step = step_create(guard_x, guard_y, NORTH);
    int part_1 = follow_col_north(grid, first_step, 0, path_tracer);
    hashset_free(path_tracer);
    path_tracer = NULL;

    printf("Part 1: %u\n", part_1);

    return EXIT_SUCCESS;
}

