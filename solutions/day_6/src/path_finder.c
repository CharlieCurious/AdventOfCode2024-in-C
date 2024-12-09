#include "path_tracer.h"
#include <path_finder.h>
#include <stdio.h>

void print_grid(Grid *grid, uint sum) {

    printf("sum: %u\n", sum);
    for (size_t i = 0; i < grid->height; i++) {
        for (size_t j = 0; j < grid->width; j++) {
            printf("%c ", grid->map[i][j]);
        }
        printf("\n");
    }
    printf("==========================\n"); 
}

static bool is_obstructed(Grid *grid, size_t x, size_t y);

uint follow_line_west(Grid *grid, Step step, uint sum) {
    sum_and_check_if_not_yet_visited(grid->map, step.x, step.y, &sum);

    Step next_step;
    while (step.y < grid->width - 1) {
        if (is_obstructed(grid, step.x, step.y + 1)) {
            next_step = step_create(step.x + 1, step.y, SOUTH);

            return follow_col_south(grid, next_step, sum);
        }

        next_step = step_create(step.x, step.y + 1, WEST);
        return follow_line_west(grid, next_step, sum);
    }

    return sum;
}

uint follow_line_east(Grid *grid, Step step, uint sum){
    sum_and_check_if_not_yet_visited(grid->map, step.x, step.y, &sum);

    Step next_step;
    while (step.y > 0) {
        if (is_obstructed(grid, step.x, step.y - 1)) {
            next_step = step_create(step.x - 1, step.y, NORTH);
            return follow_col_north(grid, next_step, sum);
        }

        next_step = step_create(step.x, step.y - 1, EAST);
        return follow_line_east(grid, next_step, sum);
    }

    return sum;
}

uint follow_col_north(Grid *grid, Step step, uint sum) {
    sum_and_check_if_not_yet_visited(grid->map, step.x, step.y, &sum);

    Step next_step;
    while (step.x > 0) {
        if (is_obstructed(grid, step.x - 1, step.y)) {
            next_step = step_create(step.x, step.y + 1, EAST);
            return follow_line_west(grid, next_step, sum);
        }

        next_step = step_create(step.x - 1, step.y, NORTH);
        return follow_col_north(grid, next_step, sum);
    }

    return sum;
}

uint follow_col_south(Grid *grid, Step step, uint sum) {
    sum_and_check_if_not_yet_visited(grid->map, step.x, step.y, &sum);

    Step next_step;
    while (step.x < grid->height - 1) {
        if (is_obstructed(grid, step.x + 1, step.y)) {
            next_step = step_create(step.x, step.y - 1, WEST);
            return follow_line_east(grid, next_step, sum);
        }

        next_step = step_create(step.x + 1, step.y, SOUTH);
        return follow_col_south(grid, next_step, sum);
    }

    return sum;
}

void sum_and_check_if_not_yet_visited(char **grid, size_t x, size_t y, uint *sum) {
    if (grid[x][y] != VISITED) {
        (*sum)++;
        grid[x][y] = VISITED;
    }
}

static bool is_obstructed(Grid *grid, size_t x, size_t y) {
    char c = grid->map[x][y];
    if (c == OBSTRUCTION || c == PRINTER)
        return true;
    return false;
}
