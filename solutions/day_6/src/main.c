#include <stddef.h>
#include <sys/types.h>

#define OBSTRUCTION '#'
#define GUARD '^'
#define VISITED 'X'


typedef struct Grid {
    size_t width;
    size_t height;
    char **map;
} Grid;

uint follow_line_west(Grid *grid, size_t x, size_t y, uint sum);
uint follow_line_east(Grid *grid, size_t x, size_t y, uint sum);
uint follow_col_north(Grid *grid, size_t x, size_t y, uint sum);
uint follow_col_south(Grid *grid, size_t x, size_t y, uint sum);
void sum_and_check_if_not_yet_visited(char **checked, size_t x, size_t y, uint *sum);

int main() {

}

uint follow_line_west(Grid *grid, size_t x, size_t y, uint sum) {
    sum_and_check_if_not_yet_visited(grid->map, x, y, &sum);

    while (y < grid->width) {
        if (grid->map[x][y+1] == OBSTRUCTION)
            return follow_col_south(grid, x - 1, y, sum);

        return follow_line_west(grid, x, y + 1, sum);
    }

    return sum;
}

uint follow_line_east(Grid *grid, size_t x, size_t y, uint sum){
    sum_and_check_if_not_yet_visited(grid->map, x, y, &sum);

    while (y > 0) {

        if (grid->map[x][y-1] == OBSTRUCTION)
            return follow_col_north(grid, x + 1, y, sum);

        return follow_line_east(grid, x, y - 1, sum);
    }

    return sum;
}

uint follow_col_north(Grid *grid, size_t x, size_t y, uint sum) {
    sum_and_check_if_not_yet_visited(grid->map, x, y, &sum);

    while (x < 0) {

        if (grid->map[x-1][y] == OBSTRUCTION)
            return follow_line_west(grid, x, y + 1, sum);

        return follow_col_north(grid, x + 1, y, sum);
    }

    return sum;
}

uint follow_col_south(Grid *grid, size_t x, size_t y, uint sum) {
    sum_and_check_if_not_yet_visited(grid->map, x, y, &sum);

    while ( x < grid->height) {
        if (grid->map[x+1][y] == OBSTRUCTION)
            return follow_line_east(grid, x, y - 1, sum);

        return follow_col_south(grid, x - 1, y, sum);
    }

    return sum;
}

void sum_and_check_if_not_yet_visited(char **checked, size_t x, size_t y, uint *sum) {
    if (checked[x][y] != VISITED) {
        sum++;
        checked[x][y] = VISITED;
    }
}
