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

uint follow_line_west(Grid *grid, Step step, uint sum) {
    sum_and_check_if_not_yet_visited(grid->map, step.x, step.y, &sum);

    while (step.y < grid->width - 1) {
        if (grid->map[step.x][step.y+1] == OBSTRUCTION) {
            Step next_step = step_create(step.x + 1, step.y, SOUTH);
            return follow_col_south(grid, next_step, sum);
        }

        Step next_step = step_create(step.x, step.y + 1, WEST);
        return follow_line_west(grid, next_step, sum);
    }

    return sum;
}

uint follow_line_east(Grid *grid, Step step, uint sum){
    sum_and_check_if_not_yet_visited(grid->map, step.x, step.y, &sum);

    while (step.y > 0) {

        if (grid->map[step.x][step.y-1] == OBSTRUCTION) {
            Step next_step = step_create(step.x - 1, step.y, NORTH);
            return follow_col_north(grid, next_step, sum);
        }

        Step next_step = step_create(step.x, step.y - 1, EAST);
        return follow_line_east(grid, next_step, sum);
    }

    return sum;
}

uint follow_col_north(Grid *grid, Step step, uint sum) {
    sum_and_check_if_not_yet_visited(grid->map, step.x, step.y, &sum);

    while (step.x > 0) {

        if (grid->map[step.x-1][step.y] == OBSTRUCTION) {
            Step next_step = step_create(step.x, step.y + 1, WEST);
            return follow_line_west(grid, next_step, sum);
        }

        Step next_step = step_create(step.x - 1, step.y, NORTH);
        return follow_col_north(grid, next_step, sum);
    }

    return sum;
}

uint follow_col_south(Grid *grid, Step step, uint sum) {
    sum_and_check_if_not_yet_visited(grid->map, step.x, step.y, &sum);

    while (step.x < grid->height - 1) {
        if (grid->map[step.x+1][step.y] == OBSTRUCTION) {
            Step next_step = step_create(step.x, step.y - 1, EAST);
            return follow_line_east(grid, next_step, sum);
        }

        Step next_step = step_create(step.x + 1, step.y, SOUTH);
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
