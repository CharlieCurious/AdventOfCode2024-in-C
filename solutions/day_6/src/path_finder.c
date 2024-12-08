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
    printf("==========================\n"); }

uint follow_line_west(Grid *grid, size_t x, size_t y, uint sum) {
    sum_and_check_if_not_yet_visited(grid->map, x, y, &sum);

    while (y < grid->width - 1) {
        if (grid->map[x][y+1] == OBSTRUCTION)
            return follow_col_south(grid, x + 1, y, sum);

        return follow_line_west(grid, x, y + 1, sum);
    }

    return sum;
}

uint follow_line_east(Grid *grid, size_t x, size_t y, uint sum){
    sum_and_check_if_not_yet_visited(grid->map, x, y, &sum);

    while (y > 0) {

        if (grid->map[x][y-1] == OBSTRUCTION)
            return follow_col_north(grid, x - 1, y, sum);

        return follow_line_east(grid, x, y - 1, sum);
    }

    return sum;
}

uint follow_col_north(Grid *grid, size_t x, size_t y, uint sum) {
    sum_and_check_if_not_yet_visited(grid->map, x, y, &sum);

    while (x > 0) {

        if (grid->map[x-1][y] == OBSTRUCTION)
            return follow_line_west(grid, x, y + 1, sum);

        return follow_col_north(grid, x - 1, y, sum);
    }

    return sum;
}

uint follow_col_south(Grid *grid, size_t x, size_t y, uint sum) {
    sum_and_check_if_not_yet_visited(grid->map, x, y, &sum);

    while ( x < grid->height - 1) {
        if (grid->map[x+1][y] == OBSTRUCTION)
            return follow_line_east(grid, x, y - 1, sum);

        return follow_col_south(grid, x + 1, y, sum);
    }

    return sum;
}

void sum_and_check_if_not_yet_visited(char **grid, size_t x, size_t y, uint *sum) {
    if (grid[x][y] != VISITED) {
        (*sum)++;
        grid[x][y] = VISITED;
    }
}
